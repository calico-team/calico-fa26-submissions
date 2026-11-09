
import sys
from bisect import bisect_left, bisect_right

input = sys.stdin.readline

t = int(input())

for _ in range(t):
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

    blocked = 0

    for e, north in groups.values():
        north.sort()

        for x in e:
            left = bisect_left(north, x)
            right = bisect_right(north, x + k - 1)

            blocked += right - left

    ans = n * k - blocked

    print(ans)
