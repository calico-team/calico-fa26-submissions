import sys
from bisect import bisect_left, bisect_right
data = sys.stdin.buffer.read().split()
p = 0
t = int(data[p])
p += 1
for _ in range(t):
    n = int(data[p])
    k = int(data[p + 1])
    p += 2
    east = {}
    north = {}
    for i in range(n):
        x = int(data[p])
        y = int(data[p + 1])
        d = data[p + 3]
        p += 4
        s = x + y
        if d == b'E':
            if s not in east:
                east[s] = []
            east[s].append(x)
        else:
            if s not in north:
                north[s] = []
            north[s].append(x)
    lost = 0
    for s in east:
        if s not in north:
            continue
        positions = north[s]
        positions.sort()
        for x in east[s]:
            left = bisect_left(positions, x)
            right = bisect_right(positions, x + k - 1)
            lost += right - left
    print(n * k - lost)