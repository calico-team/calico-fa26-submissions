import sys
import math
from collections import defaultdict,deque,Counter
from heapq import heappush,heappop
from bisect import bisect_left,bisect_right,insort_left,insort_right
from functools import lru_cache,reduce
from itertools import accumulate,permutations,combinations,product
try:from functools import cache
except ImportError:cache = lru_cache(maxsize=None)

_I = 0

I = input = lambda:sys.stdin.readline().rstrip();II = lambda:int(I());MI = lambda:map(int,I().split())
_O=[];print=(lambda*a,sep=' ',end='\n',flush=True:(sys.stdout.write(sep.join(map(str,a))+end),sys.stdout.flush())) if _I else (lambda*a,sep=' ',end='\n',flush=False:_O.append(sep.join(map(str,a))+end));_p=lambda:sys.stdout.write(''.join(_O))

InF = 10**18 + 5
MOD = 10**9 + 7
MOD2 = 998244353
CFMOD = 676767677

def dsu(n): #<- from macro btw
    p = list(range(n))
    def f(x):
        while p[x]!=x:p[x]=p[p[x]];x=p[x]
        return x
    def u(a,b):
        a,b=f(a),f(b)
        if a!=b:p[a]=b
        return a!=b
    return f,u
    
def solve():
    n,m,q = MI()
    w = m+1
    qs = [tuple(MI()) for i in range(q)]
    f, u = dsu(n * w); g = [0] * (n * w)
    for cr, cc, rad in reversed(qs):
        rad2 = rad*rad
        for r in range(max(0, cr - rad), min(n - 1, cr + rad) + 1):
            d = rad2 - (r-cr)**2
            h = math.isqrt(d)
            lo, hi = max(0, cc - h), min(m - 1, cc + h)
            if lo > hi: continue
            base = r * w
            x = f(base + lo); end = base + hi
            while x <= end:
                g[x] = d - (x - base - cc)**2 + 1; u(x, x + 1); x = f(x)
    for r in range(n): print(*g[r*w:r*w+m])

t = 1
t = II()
for i in range(t):solve()
if not _I:_p()