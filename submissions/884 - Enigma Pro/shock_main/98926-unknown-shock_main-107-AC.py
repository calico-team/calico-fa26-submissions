import sys


def main():
    data = sys.stdin.buffer.read().split()
    pos = 0
    t = int(data[pos]); pos += 1
    out = []
    wcache = {}
    for _ in range(t):
        n = int(data[pos]); m = int(data[pos + 1]); q = int(data[pos + 2]); pos += 3
        rs = [0] * q
        cs = [0] * q
        ps = [0] * q
        for i in range(q):
            rs[i] = int(data[pos]); cs[i] = int(data[pos + 1]); ps[i] = int(data[pos + 2]); pos += 3
        st = m + 1
        nxt = list(range(n * st))
        val = [0] * (n * st)
        best = {}
        for i in range(q - 1, -1, -1):
            R = rs[i]; C = cs[i]; P = ps[i]
            key = R * st + C
            bp = best.get(key, -1)
            if bp >= P:
                continue
            best[key] = P
            ws = wcache.get(P)
            if ws is None:
                ws = [0] * (P + 1)
                pp = P * P
                w = P
                for dr in range(P + 1):
                    lim = pp - dr * dr
                    while w * w > lim:
                        w -= 1
                    ws[dr] = w
                wcache[P] = ws
            pp1 = P * P + 1
            center = R * st + C
            for dr in range(P + 1):
                w = ws[dr]
                base = pp1 - dr * dr
                cc = center - dr * st
                lo = cc - w
                hi = cc + w
                x = lo
                while nxt[x] != x:
                    y = nxt[nxt[x]]
                    nxt[x] = y
                    x = y
                if x <= hi:
                    while x <= hi:
                        d = x - cc
                        val[x] = base - d * d
                        nxt[x] = x + 1
                        x += 1
                        while nxt[x] != x:
                            y = nxt[nxt[x]]
                            nxt[x] = y
                            x = y
                    nxt[lo] = x
                if dr:
                    cc = center + dr * st
                    lo = cc - w
                    hi = cc + w
                    x = lo
                    while nxt[x] != x:
                        y = nxt[nxt[x]]
                        nxt[x] = y
                        x = y
                    if x <= hi:
                        while x <= hi:
                            d = x - cc
                            val[x] = base - d * d
                            nxt[x] = x + 1
                            x += 1
                            while nxt[x] != x:
                                y = nxt[nxt[x]]
                                nxt[x] = y
                                x = y
                        nxt[lo] = x
        for r in range(n):
            off = r * st
            out.append(' '.join(map(str, val[off:off + m])) + ' ')
    sys.stdout.write('\n'.join(out))
    sys.stdout.write('\n')


main()
