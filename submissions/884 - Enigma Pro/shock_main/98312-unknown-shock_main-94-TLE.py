import sys


def main():
    data = sys.stdin.buffer.read().split()
    pos = 0
    t = int(data[pos]); pos += 1
    out = []
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
        for i in range(q - 1, -1, -1):
            R = rs[i]; C = cs[i]; P = ps[i]
            pp = P * P
            w = P
            dr = 0
            while dr <= P:
                lim = pp - dr * dr
                while w * w > lim:
                    w -= 1
                base = lim + 1
                k = 0
                while k < 2:
                    if k == 0:
                        row = R - dr
                    else:
                        if dr == 0:
                            break
                        row = R + dr
                    k += 1
                    off = row * st
                    lo = off + C - w
                    hi = off + C + w
                    x = lo
                    while nxt[x] != x:
                        y = nxt[nxt[x]]
                        nxt[x] = y
                        x = y
                    if x > hi:
                        continue
                    cc = off + C
                    while x <= hi:
                        d = x - cc
                        val[x] = base - d * d
                        nxt[x] = x + 1
                        x += 1
                        z = x
                        while nxt[z] != z:
                            y = nxt[nxt[z]]
                            nxt[z] = y
                            z = y
                        x = z
                    nxt[lo] = x
                dr += 1
        for r in range(n):
            off = r * st
            out.append(' '.join(map(str, val[off:off + m])) + ' ')
    sys.stdout.write('\n'.join(out))
    sys.stdout.write('\n')


main()
