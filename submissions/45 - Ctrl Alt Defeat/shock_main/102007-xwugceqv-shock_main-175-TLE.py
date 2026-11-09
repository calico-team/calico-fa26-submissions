import math
import sys

input = sys.stdin.readline
print = sys.stdout.write

ii = lambda: int(input())
mii = lambda: map(int, input().split())


for _ in range(ii()):
    n, m, q = mii()
    rows, cols, pows = [], [], []
    starts = [[] for _ in range(n)]
    for i in range(q):
        r, c, p = mii()
        rows.append(r)
        cols.append(c)
        pows.append(p)
        starts[max(0, r - p)].append(i)

    out = []
    active = []
    for row in range(n):
        if starts[row]:
            active.extend(starts[row])
            active.sort()
        active = [i for i in active if rows[i] + pows[i] >= row]
        if not active:
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

        for i in active[::-1]:
            r, c, p = rows[i], cols[i], pows[i]
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
