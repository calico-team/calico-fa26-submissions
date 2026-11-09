import sys
from math import isqrt

def solve():
    inp = sys.stdin.buffer.readline
    t = int(inp())
    res = []

    for _ in range(t):
        n, m, q = map(int, inp().split())
        qs = [tuple(map(int, inp().split())) for _ in range(q)]

        g = [[0] * m for _ in range(n)]
        free = [(1 << m) - 1 for _ in range(n)]
        seen = {}
        cache = {}

        for r, c, p in reversed(qs):
            if seen.get((r, c), -1) >= p:
                continue
            seen[r, c] = p

            if p not in cache:
                offs = []
                for d in range(-p, p + 1):
                    w = isqrt(p * p - d * d)
                    mask = (1 << (2 * w + 1)) - 1
                    offs.append((d, w, p * p - d * d + 1, mask))
                cache[p] = offs

            for d, w, pw, mask in cache[p]:
                row = r + d
                bits = free[row] & (mask << (c - w))

                if not bits:
                    continue

                free[row] ^= bits

                while bits:
                    bit = bits & -bits
                    col = bit.bit_length() - 1
                    g[row][col] = pw - (col - c) ** 2
                    bits -= bit

        for row in g:
            res.append(" ".join(map(str, row)))

    sys.stdout.write("\n".join(res))

if __name__ == "__main__":
    solve()