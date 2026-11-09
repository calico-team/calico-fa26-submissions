
import sys
from bisect import bisect_right
from collections import defaultdict

input = sys.stdin.readline


class Fenwick:
    def __init__(self, n):
        self.n = n
        self.bit = [0] * (n + 1)

    def add(self, i):
        while i <= self.n:
            self.bit[i] += 1
            i += i & -i

    def sum(self, i):
        ans = 0
        while i > 0:
            ans += self.bit[i]
            i -= i & -i
        return ans


def count_blocked(points, queries):
    if not points or not queries:
        return 0

    heights = sorted(set(z for x, z in points))
    points.sort()

    events = []

    for i, (L, R, z) in enumerate(queries):
        events.append((R, i, z, 1))
        events.append((L - 1, i, z, -1))

    events.sort()

    bit = Fenwick(len(heights))
    answers = [0] * len(queries)

    p = 0
    inserted = 0

    for boundary, idx, z, sign in events:

        while p < len(points) and points[p][0] <= boundary:
            px, pz = points[p]

            pos = bisect_right(heights, pz)
            bit.add(pos)

            inserted += 1
            p += 1

        pos = bisect_right(heights, z)

        greater = inserted - bit.sum(pos)

        answers[idx] += sign * greater

    return sum(answers)


def solve():
    T = int(input())

    for _ in range(T):
        N, K = map(int, input().split())

        groups = defaultdict(lambda: [[], []])

        for _ in range(N):
            x, y, z, d = input().split()

            x, y, z = int(x), int(y), int(z)

            if d == 'E':
                groups[x + y][0].append((x, z))
            else:
                groups[x + y][1].append((x, z))

        blocked = 0

        for east, north in groups.values():

            # North-moving drones block East-moving drones
            queries = [
                (x + 1, x + K - 1, z)
                for x, z in east
            ]

            blocked += count_blocked(north, queries)

            # East-moving drones block North-moving drones
            queries = [
                (x - K + 1, x - 1, z)
                for x, z in north
            ]

            blocked += count_blocked(east, queries)

        print(N * K - blocked)


if __name__ == "__main__":
    solve()
