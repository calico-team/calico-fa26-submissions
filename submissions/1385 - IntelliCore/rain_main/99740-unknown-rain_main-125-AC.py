from bisect import bisect_left, bisect_right

T = int(input())

for i in range(T):
    n, k = map(int, input().split())

    groups = {}

    for i in range(n):
        x, y, z, d = input().split()
        x = int(x)
        y = int(y)

        s = x + y

        if s not in groups:
            groups[s] = [[], []]

        if d == "E":
            groups[s][0].append(x)
        else:
            groups[s][1].append(x)

    meetings = 0

    for east, north in groups.values():
        north.sort()

        for x in east:
            left = bisect_right(north, x)
            right = bisect_left(north, x + k)

            meetings += right - left

    answer = (n * k) - meetings

    print(answer)