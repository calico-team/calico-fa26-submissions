import sys
from bisect import bisect_left, bisect_right


def read_drones(data, pos, n):
    east = []
    north = {}

    for i in range(n):
        x = int(data[pos])
        y = int(data[pos + 1])
        d = data[pos + 3]
        pos = pos + 4

        if d == "E":
            east.append((x, y))
        else:
            s = x + y
            if s not in north:
                north[s] = []
            north[s].append(x)

    for s in north:
        north[s].sort()

    return east, north, pos


def count_meetings(east, north, k):
    meetings = 0

    for x, y in east:
        s = x + y
        if s in north:
            xs = north[s]
            left = bisect_left(xs, x)
            right = bisect_right(xs, x + k - 1)
            meetings = meetings + (right - left)

    return meetings


def main():
    data = sys.stdin.read().split()
    pos = 0

    t = int(data[pos])
    pos = pos + 1

    output = []

    for i in range(t):
        n = int(data[pos])
        k = int(data[pos + 1])
        pos = pos + 2

        east, north, pos = read_drones(data, pos, n)
        meetings = count_meetings(east, north, k)

        output.append(str(n * k - meetings))

    print("\n".join(output))


main()