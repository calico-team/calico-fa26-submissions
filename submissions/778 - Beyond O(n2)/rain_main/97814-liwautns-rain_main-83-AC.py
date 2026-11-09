import sys
from bisect import bisect_left, bisect_right

input = sys.stdin.buffer.readline

t = int(input())
answers = []

for _ in range(t):
    n, k = map(int, input().split())
    groups = {}

    for _ in range(n):
        x, y, z, direction = input().split()
        x = int(x)
        y = int(y)
        z = int(z)

        diagonal = x + y
        if diagonal not in groups:
            groups[diagonal] = [[], []]

        if direction == b"E":
            groups[diagonal][0].append((x, z))
        else:
            groups[diagonal][1].append((x, z))

    blocked = 0

    for east, north in groups.values():
        if not east or not north:
            continue

        north.sort()
        north_x = []
        height_x = {}

        for x, z in north:
            north_x.append(x)
            if z not in height_x:
                height_x[z] = []
            height_x[z].append(x)

        for x, z in east:
            left = bisect_right(north_x, x)
            right = bisect_left(north_x, x + k)
            all_meetings = right - left

            same_height = height_x.get(z, [])
            same_left = bisect_right(same_height, x)
            same_right = bisect_left(same_height, x + k)
            equal_height_meetings = same_right - same_left

            blocked += all_meetings - equal_height_meetings

    answers.append(str(n * k - blocked))

print("\n".join(answers))