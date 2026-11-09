import sys
from bisect import bisect_left, bisect_right

from collections import defaultdict

test_cases = int(input())

for a in range(test_cases):
    drone_count, nights = map(int, input().split())

    # x+y will +1 for EVERYONE, so drones only meet others from their diagonal

    east = defaultdict(list)
    north = defaultdict(list)

    for b in range(drone_count):
        x, y, height, direction = input().split()
        x = int(x)
        y = int(y)

        if direction == "E":
            east[x + y].append(x)
        else:
            north[x + y].append(x)

    meetings = 0

    for diagonal in east:
        targets = sorted(north[diagonal])

        for column in east[diagonal]:
            # catch any north drone at most nights - 1 columns ahead
            first = bisect_left(targets, column)
            last = bisect_right(targets, column + nights - 1)
            meetings += last - first

    print(drone_count * nights - meetings)