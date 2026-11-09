import sys
from math import isqrt
input = sys.stdin.readline
    
for _ in range(int(input())):
    n,m,q = map(int, input().split())
    quakes = [tuple(map(int, input().split())) for _ in range(q)]
    grid = [[0] * m for _ in range(n)]
    nxt = [list(range(m + 1)) for _ in range(n)]
    
    def find(row, c):
        a = nxt[row]
        root = c
        while a[root] != root:
            root = a[root]
        while a[c] != root:
            a[c], c = root, a[c]
        return root

    for r, c, p in reversed(quakes):
        for row in range(r - p, r + p + 1):
            diff = p * p - (row - r) ** 2
            d = isqrt(diff)
            col = find(row, c - d)
            while col <= c + d:
                grid[row][col] = diff - (col - c) ** 2 + 1
                nxt[row][col] = col + 1
                col = find(row, col + 1)
    
    print("\n".join(" ".join(map(str, line)) for line in grid))