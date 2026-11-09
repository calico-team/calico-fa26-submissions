import sys
from bisect import bisect_right

data = sys.stdin.buffer.read().split()
idx = 0
T = int(data[idx]); idx += 1
out = []
for _ in range(T):
    n = int(data[idx]); k = int(data[idx + 1]); idx += 2
    # E and N drones only ever meet if they have the same x+y, and its after (north x - east x) nights
    east = {}
    north = {}
    for i in range(n):
        x = int(data[idx]); y = int(data[idx + 1]); d = data[idx + 3]; idx += 4
        if d == b"E":
            east.setdefault(x + y, []).append(x)
        else:
            north.setdefault(x + y, []).append(x)
    blocked = 0
    for s, xs in east.items():
        if s not in north:
            continue
        ns = sorted(north[s])
        for x in xs:
            # only counts if they meet on one of nights 1..k-1
            blocked += bisect_right(ns, x + k - 1) - bisect_right(ns, x)
    out.append(n * k - blocked)
print("\n".join(map(str, out)))
