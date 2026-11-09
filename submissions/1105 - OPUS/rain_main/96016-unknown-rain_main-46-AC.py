from collections import defaultdict
from bisect import bisect_left, bisect_right

def solve():
    T = int(input())

    for _ in range(T):
        n, days = map(int, input().split())

        east = defaultdict(list)
        north = []

        for _ in range(n):
            x, y, z, direction = input().split()
            x, y = int(x), int(y)

            if direction == 'E':
                east[x + y].append(x)
            else:
                north.append((x + y, x))

        for positions in east.values():
            positions.sort()

        collisions = 0

        for diagonal, x in north:
            positions = east[diagonal]

            left = bisect_left(positions, x - days + 1)
            right = bisect_right(positions, x)

            collisions += right - left

        print(n * days - collisions)

solve()