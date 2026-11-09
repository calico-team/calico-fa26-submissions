
import sys
from collections import defaultdict
from bisect import bisect_left, bisect_right


def count_blocked(points, queries):
    if not points or not queries:
        return 0

    xs = sorted(x for x, z in points)
    m = len(xs)

    bit = [0] * (m + 1)

    points.sort(key=lambda p: p[1], reverse=True)
    queries.sort(key=lambda q: q[2], reverse=True)

    p = 0
    total = 0

    for lo, hi, height in queries:
        while p < len(points) and points[p][1] > height:
            x, z = points[p]
            idx = bisect_left(xs, x) + 1

            while idx <= m:
                bit[idx] += 1
                idx += idx & -idx

            p += 1

        left = bisect_left(xs, lo)
        right = bisect_right(xs, hi)

        s = 0
        idx = right
        while idx > 0:
            s += bit[idx]
            idx -= idx & -idx

        idx = left
        while idx > 0:
            s -= bit[idx]
            idx -= idx & -idx

        total += s

    return total


def solve():
    input = sys.stdin.readline
    T = int(input())

    for _ in range(T):
        N, K = map(int, input().split())

        groups = defaultdict(lambda: [[], []])

        for _ in range(N):
            x, y, z, d = input().split()
            x = int(x)
            y = int(y)
            z = int(z)

            if d == 'E':
                groups[x + y][0].append((x, z))
            else:
                groups[x + y][1].append((x, z))

        blocked = 0

        for east, north in groups.values():
            if not east or not north:
                continue

            # East-moving drones blocked by higher north-moving drones
            east_queries = [
                (x, x + K - 1, z)
                for x, z in east
            ]

            blocked += count_blocked(north, east_queries)

            # North-moving drones blocked by higher east-moving drones
            north_queries = [
                (x - K + 1, x, z)
                for x, z in north
            ]

            blocked += count_blocked(east, north_queries)

        print(N * K - blocked)


if __name__ == "__main__":
    solve()
