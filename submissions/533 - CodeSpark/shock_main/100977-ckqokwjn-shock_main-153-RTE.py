import sys
from math import isqrt

def main():
    data = sys.stdin.buffer.read().split()
    p = 0
    t = int(data[p]); p += 1
    out = []
    wcache = {}
    for _ in range(t):
        n = int(data[p]); m = int(data[p+1]); q = int(data[p+2]); p += 3
        qs = data[p:p+3*q]; p += 3*q
        W = m + 1
        nxt = list(range(n * W))
        res = [0] * (n * W)
        remain = [m] * n
        left = n * m
        for i in range(q - 1, -1, -1):
            if left == 0:
                break
            R = int(qs[3*i]); C = int(qs[3*i+1]); P = int(qs[3*i+2])
            ws = wcache.get(P)
            if ws is None:
                P2 = P * P
                ws = [isqrt(P2 - d * d) for d in range(P + 1)]
                wcache[P] = ws
            P2p1 = P * P + 1
            r0 = R - P
            if r0 < 0: r0 = 0
            r1 = R + P
            if r1 > n - 1: r1 = n - 1
            for r in range(r0, r1 + 1):
                if remain[r] == 0:
                    continue
                dr = r - R
                if dr < 0:
                    dr = -dr
                w = ws[dr]
                base = r * W
                lo = base + C - w
                if lo < base: lo = base
                hi = base + C + w
                if hi > base + m - 1: hi = base + m - 1
                x = lo
                while nxt[x] != x:
                    nxt[x] = nxt[nxt[x]]
                    x = nxt[x]
                if x > hi:
                    continue
                v0 = P2p1 - dr * dr
                cnt = 0
                while x <= hi:
                    d = x - base - C
                    res[x] = v0 - d * d
                    nxt[x] = x + 1
                    cnt += 1
                    x += 1
                    while nxt[x] != x:
                        nxt[x] = nxt[nxt[x]]
                        x = nxt[x]
                remain[r] -= cnt
                left -= cnt
        for r in range(n):
            b = r * W
            out.append(" ".join(map(str, res[b:b+m])))
    sys.stdout.write("\n".join(out) + "\n")

main()