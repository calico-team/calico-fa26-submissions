
import sys
from collections import defaultdict
from bisect import bisect_left, bisect_right


class Fenwick:
    def __init__(self, n):
        self.n = n
        self.bit = [0] * (n + 1)

    def update(self, i):
        while i <= self.n:
            self.bit[i] += 1
            i += i & -i

    def query(self, i):
        result = 0
        while i > 0:
            result += self.bit[i]
            i -= i & -i
        return result

    def range_query(self, l, r):
        return self.query(r) - self.query(l)


def solve():
    input = sys.stdin.readline

    T = int(input())

    for _ in range(T):
        N, K = map(int, input().split())

        groups = defaultdict(list)

        for _ in range(N):
            x, y, z, d = input().split()
            x, y, z = int(x), int(y), int(z)

            groups[x + y].append((z, x, d))

        blocked = 0

        for drones in groups.values():

            # Sort by decreasing height
            drones.sort(reverse=True)

            # Coordinate compression
            xs = sorted(set(x for z, x, d in drones))

            m = len(xs)

            east = Fenwick(m)
            north = Fenwick(m)

            i = 0

            while i < len(drones):

                j = i

                # Find drones with equal height
                while j < len(drones) and drones[j][0] == drones[i][0]:
                    j += 1

                # Query before inserting equal-height drones
                for p in range(i, j):

                    z, x, d = drones[p]

                    if d == 'E':

                        # Higher north-moving drones
                        # with x-coordinate in [x, x + K - 1]

                        l = bisect_left(xs, x)
                        r = bisect_right(xs, x + K - 1)

                        blocked += north.range_query(l, r)

                    else:

                        # Higher east-moving drones
                        # with x-coordinate in [x - K + 1, x]

                        l = bisect_left(xs, x - K + 1)
                        r = bisect_right(xs, x)

                        blocked += east.range_query(l, r)

                # Insert all drones of the current height
                for p in range(i, j):

                    z, x, d = drones[p]

                    pos = bisect_left(xs, x) + 1

                    if d == 'E':
                        east.update(pos)
                    else:
                        north.update(pos)

                i = j

        total = N * K
        print(total - blocked)


if __name__ == "__main__":
    solve()
