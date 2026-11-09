import sys
from bisect import bisect_left, bisect_right
from collections import defaultdict

def solve():
    dataa = sys.stdin.read().split()
    T = int(dataa[0])
    indexx = 1
    out = []
    for _ in range(T):
        n = int(dataa[indexx]); k = int(dataa[indexx + 1]); indexx += 2
        est = defaultdict(list)
        nrth = defaultdict(list)
        for item in range(n):
            x = int(dataa[indexx]); y = int(dataa[indexx + 1])
            d = dataa[indexx + 3]
            indexx += 4
            if d == 'E':
                est[x + y].append(x)
            else:
                nrth[x + y].append(x)

        pairs = 0
        for s, nx in nrth.items():
            ex = est.get(s)
            if not ex:
                continue
            ex.sort()
            for x2 in nx:
                low = bisect_left(ex, x2 - k + 1)
                high = bisect_right(ex, x2)
                pairs += high - low

        out.append(str(n * k - pairs))
    print('\n'.join(out))

solve()