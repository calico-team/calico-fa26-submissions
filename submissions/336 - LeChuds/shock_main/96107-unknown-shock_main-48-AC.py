from math import isqrt
from itertools import repeat
from operator import add, sub

w = {}
for _ in range(int(input())):
    n, m, q = map(int, input().split())
    qs = [tuple(map(int, input().split())) for _ in range(q)]
    a = [[0] * m for _ in range(n)]
    s = [bytearray(b"\1" * m) for _ in range(n)]
    for r0, c0, p in reversed(qs):
        if p not in w:
            w[p] = [isqrt(p * p - i * i) for i in range(-p, p + 1)]
        rows = s[r0 - p:r0 + p + 1]
        lo = map(sub, repeat(c0), w[p])
        hi = map(add, repeat(c0 + 1), w[p])
        f = list(map(bytearray.find, rows, repeat(1), lo, hi))
        if max(f) < 0:
            continue
        for row, out, i, k, j in zip(rows, a[r0 - p:r0 + p + 1], range(-p, p + 1), w[p], f):
            while j >= 0:
                out[j] = p * p - i * i - (j - c0) ** 2 + 1
                row[j] = 0
                j = row.find(1, j + 1, c0 + k + 1)
    print("\n".join(" ".join(map(str, row)) for row in a))
