"""
* Return an integer denoting the amount of rain collected after the Kth nights 
*
* N: Number of drones
* K: Number of nights
* L: a list in this order [X, Y, Z, D] for each drone
*   X: Starting X location of Drone
*   Y: Starting Y location of Drone
*   Z: Starting Z location of Drone
*   D: Starting direction of Drone
"""

from collections import defaultdict
from bisect import bisect_left, bisect_right


class Fenwick:
    def __init__(self, n):
        self.n = n
        self.tree = [0] * (n + 1)

    def update(self, i, value):
        while i <= self.n:
            self.tree[i] += value
            i += i & -i

    def query(self, i):
        total = 0
        while i > 0:
            total += self.tree[i]
            i -= i & -i
        return total

    def range_sum(self, left, right):
        return self.query(right) - self.query(left - 1)


def solve(N: int, K: int, L: list):

    groups = defaultdict(lambda: {"E": [], "N": []})

    for x, y, z, d in L:
        groups[x + y][d].append((x, z))

    blocked = 0

    for group in groups.values():

        east = group["E"]
        north = group["N"]

        if not east or not north:
            continue

        # East drone is lower
        coords = sorted(set(x for x, z in north))
        bit = Fenwick(len(coords))

        north_sorted = sorted(north, key=lambda p: -p[1])
        east_sorted = sorted(east, key=lambda p: -p[1])

        j = 0

        for x, z in east_sorted:

            while j < len(north_sorted) and north_sorted[j][1] > z:
                nx, nz = north_sorted[j]
                pos = bisect_left(coords, nx) + 1
                bit.update(pos, 1)
                j += 1

            left = bisect_left(coords, x + 1) + 1
            right = bisect_right(coords, x + K - 1)

            blocked += bit.range_sum(left, right)

        # North drone is lower
        coords = sorted(set(x for x, z in east))
        bit = Fenwick(len(coords))

        east_sorted = sorted(east, key=lambda p: -p[1])
        north_sorted = sorted(north, key=lambda p: -p[1])

        j = 0

        for x, z in north_sorted:

            while j < len(east_sorted) and east_sorted[j][1] > z:
                ex, ez = east_sorted[j]
                pos = bisect_left(coords, ex) + 1
                bit.update(pos, 1)
                j += 1

            left = bisect_left(coords, x - (K - 1)) + 1
            right = bisect_right(coords, x - 1)

            blocked += bit.range_sum(left, right)

    return N * K - blocked


def main():
    T = int(input())
    for _ in range(T):
        N, K = map(int, input().split())
        L = []
        for _ in range(N):
            X, Y, Z, D = input().split()
            L.append((int(X), int(Y), int(Z), D))

        print(solve(N, K, L))

if __name__ == '__main__':
    main()