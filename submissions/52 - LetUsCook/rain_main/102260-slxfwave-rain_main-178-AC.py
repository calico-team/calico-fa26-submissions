import sys
from bisect import bisect_left as bl, bisect_right as br
from collections import defaultdict as dd

d = sys.stdin.read().split(); p = 1
for _ in range(int(d[0])):
    n, k = int(d[p]), int(d[p+1]); p += 2
    E, N = dd(list), dd(list)
    for _ in range(n):
        x, y, c = int(d[p]), int(d[p+1]), d[p+3]; p += 4
        (E if c == 'E' else N)[x+y].append(x)
    m = 0
    for s, xs in N.items():
        e = sorted(E[s])
        m += sum(br(e, x) - bl(e, x-k+1) for x in xs)
    print(n*k - m)
