import math
import sys

input = sys.stdin.readline
print = sys.stdout.write

ii = lambda: int(input())
mii = lambda: map(int, input().split())


for _ in range(ii()):
    n, m, q = mii()
    quake_rows = [[] for _ in range(n)]
    for _ in range(q):
        r, c, p = mii()
        rmin = max(0, r - p)
        rmax = min(n - 1, r + p)
        for rr in range(rmin, rmax + 1):
            quake_rows[rr].append((r, c, p))

    out = []
    for row in range(n):
        if not quake_rows[row]:
            out.append(" ".join(["0"] * m))
            continue

        g = [0] * m
        parent = list(range(m + 1))

        def find(j):
            root = j
            while parent[root] != root:
                root = parent[root]
            while parent[j] != root:
                parent[j], j = root, parent[j]
            return root

        for r, c, p in quake_rows[row][::-1]:
            p2, r2 = p**2, (row - r) ** 2
            diff = p2 - r2
            if diff < 0:
                continue
            d = math.isqrt(diff)
            left, right = max(0, c - d), min(m - 1, c + d)
            curr = find(left)
            while curr <= right:
                g[curr] = diff - (curr - c) ** 2 + 1
                nc = find(curr + 1)
                parent[curr] = nc
                curr = nc
        out.append(" ".join(map(str, g)))
    print("\n".join(out) + "\n")
