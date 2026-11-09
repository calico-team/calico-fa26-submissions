#
#    Author: mikelou
#

import sys
import math
from collections import defaultdict,deque,Counter
from heapq import heappush,heappop
from bisect import bisect_left,bisect_right,insort_left,insort_right
from functools import lru_cache,reduce
from itertools import accumulate,permutations,combinations,product
try:from functools import cache
except ImportError:cache = lru_cache(maxsize=None)

_I = 1

I = input = lambda:sys.stdin.readline().rstrip();II = lambda:int(I());MI = lambda:map(int,I().split())
_O=[];print=(lambda*a,sep=' ',end='\n',flush=True:(sys.stdout.write(sep.join(map(str,a))+end),sys.stdout.flush())) if _I else (lambda*a,sep=' ',end='\n',flush=False:_O.append(sep.join(map(str,a))+end));_p=lambda:sys.stdout.write(''.join(_O))

INF = 10**18 + 5
MOD = 10**9 + 7
MOD2 = 998244353
CFMOD = 676767677

def solve():
    n,k = MI()
    l = list(I().split())
    print(l[0]*n)
    for x in l:
        n = I()
        if I() == "CORRECT":
            sys.exit(0)
        else:
            print(n.replace("_",x))

t = 1
t = II()
for i in range(t):solve()
if not _I:_p()
