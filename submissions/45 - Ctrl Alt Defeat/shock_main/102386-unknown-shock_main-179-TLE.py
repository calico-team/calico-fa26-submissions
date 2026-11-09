import sys
from math import isqrt
input = sys.stdin.readline

def find(a, c):
    root = c
    while a[root] != root:
        root = a[root]
    while a[c] != root:
        a[c], c = root, a[c]
    return root

out = []
for _ in range(int(input())):
    n, m, q = map(int, input().split())
    quakes = [tuple(map(int, input().split())) for _ in range(q)]
    grid = [[0] * m for _ in range(n)]
    nxt = [list(range(m + 1)) for _ in range(n)]

    for r, c, p in reversed(quakes):
        for row in range(r - p, r + p + 1):
            diff = p * p - (row - r) * (row - r)
            d = isqrt(diff)
            a = nxt[row]
            g = grid[row]
            col = find(a, c - d)
            while col <= c + d:
                g[col] = diff - (col - c) * (col - c) + 1
                a[col] = col + 1
                col = find(a, col + 1)

    out.append("\n".join(" ".join(map(str, line)) for line in grid))
sys.stdout.write("\n".join(out) + "\n")