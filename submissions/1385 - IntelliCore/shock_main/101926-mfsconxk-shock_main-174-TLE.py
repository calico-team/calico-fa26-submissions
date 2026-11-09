import sys
from math import isqrt

data = iter(map(int, sys.stdin.buffer.read().split()))

T = next(data)
output = []

for i in range(T):
    n = next(data)
    m = next(data)
    q = next(data)

    earthquakes = []

    for i in range(q):
        r = next(data)
        c = next(data)
        p = next(data)
        earthquakes.append((r, c, p))

    answer = [0] * (n * m)
    parent = list(range(n * (m + 1)))

    for r0, c0, p in reversed(earthquakes):
        p2 = p * p

        for dy in range(-p, p + 1):
            r = r0 + dy
            d = isqrt(p2 - dy * dy)

            left = c0 - d
            right = c0 + d

            base = r * (m + 1)
            pos = base + left
            end = base + right

            while parent[pos] != pos:
                parent[pos] = parent[parent[pos]]
                pos = parent[pos]

            row_start = r * m

            while pos <= end:
                c = pos - base

                answer[row_start + c] = p2 - dy * dy - (c - c0) ** 2 + 1

                nxt = pos + 1

                while parent[nxt] != nxt:
                    parent[nxt] = parent[parent[nxt]]
                    nxt = parent[nxt]

                parent[pos] = nxt
                pos = nxt

    for r in range(n):
        start = r * m
        output.append(" ".join(map(str, answer[start:start + m])))

sys.stdout.write("\n".join(output))