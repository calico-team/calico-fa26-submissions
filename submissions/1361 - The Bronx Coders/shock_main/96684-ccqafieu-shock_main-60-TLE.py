import sys
from math import isqrt


def main():
    data = sys.stdin.buffer.read().split()
    t = int(data[0])
    pos = 1
    out = []
    for _ in range(t):
        n, m, q = int(data[pos]), int(data[pos + 1]), int(data[pos + 2])
        pos += 3
        quakes = data[pos:pos + 3 * q]
        pos += 3 * q
        w = m + 1
        nxt = list(range(n * w))
        val = [0] * (n * w)
        maxp = 0
        for i in range(2, 3 * q, 3):
            p = int(quakes[i])
            if p > maxp:
                maxp = p
        root = [isqrt(x) for x in range(maxp * maxp + 1)]
        for i in range(3 * q - 3, -1, -3):
            r0 = int(quakes[i]); c0 = int(quakes[i + 1]); p = int(quakes[i + 2])
            p2 = p * p
            top = p2 + 1
            for dr in range(-p, p + 1):
                d2 = dr * dr
                h = root[p2 - d2]
                base = (r0 + dr) * w
                x = base + c0 - h
                end = base + c0 + h
                while True:
                    y = nxt[x]
                    if y == x:
                        break
                    z = nxt[y]
                    if z == y:
                        nxt[x] = y
                        x = y
                        break
                    nxt[x] = z
                    x = z
                while x <= end:
                    dc = x - base - c0
                    val[x] = top - d2 - dc * dc
                    nxt[x] = x + 1
                    x += 1
                    while True:
                        y = nxt[x]
                        if y == x:
                            break
                        z = nxt[y]
                        if z == y:
                            nxt[x] = y
                            x = y
                            break
                        nxt[x] = z
                        x = z
        for r in range(n):
            out.append(" ".join(map(str, val[r * w:r * w + m])))
    sys.stdout.write("\n".join(out) + "\n")


main()
