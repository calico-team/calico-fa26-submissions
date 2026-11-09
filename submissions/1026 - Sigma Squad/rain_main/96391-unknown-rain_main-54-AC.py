import sys
from bisect import bisect_left, bisect_right
from collections import defaultdict

def main():
    data = sys.stdin.buffer.read().split()
    p = 0
    t = int(data[p]); p += 1
    out = []
    for _ in range(t):
        n = int(data[p]); k = int(data[p+1]); p += 2
        east = defaultdict(list)
        north = []
        for i in range(n):
            x = int(data[p]); y = int(data[p+1]); d = data[p+3]; p += 4
            if d == b'E':
                east[x+y].append(x)
            else:
                north.append((x+y, x))
        for v in east.values():
            v.sort()
        bad = 0
        for s, x in north:
            if s in east:
                v = east[s]
                bad += bisect_right(v, x) - bisect_left(v, x-k+1)
        out.append(n*k - bad)
    print('\n'.join(map(str, out)))

main()
