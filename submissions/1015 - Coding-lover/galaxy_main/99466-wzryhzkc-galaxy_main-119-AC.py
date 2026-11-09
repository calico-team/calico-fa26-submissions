t = int(input())
for _ in range(t):
    n, m, q = map(int, input().split())
    g = []
    i = 0
    while i < n:
        g.append(input().strip())
        i = i + 1
    queries = []
    i = 0
    while i < q:
        queries.append(list(map(int, input().split())))
        i = i + 1
    total = 2 * n * m
    par = list(range(total))
    sz = [1] * total
    def find(x):
        while par[x] != x:
            par[x] = par[par[x]]
            x = par[x]
        return x
    def join(a, b):
        ra = find(a)
        rb = find(b)
        if ra == rb:
            return
        if sz[ra] < sz[rb]:
            temp = ra
            ra = rb
            rb = temp
        par[rb] = ra
        sz[ra] = sz[ra] + sz[rb]
    for r in range(n):
        for c in range(m):
            cell = g[r][c]
            base = r * m + c
            if cell == ".":
                join(base, base + n * m)
            if c + 1 < m:
                cell2 = g[r][c + 1]
                if cell == "." or cell == "B":
                    if cell2 == "." or cell2 == "B":
                        join(base, base + 1)
                if cell == "." or cell == "R":
                    if cell2 == "." or cell2 == "R":
                        join(base + n * m, base + 1 + n * m)
            if r + 1 < n:
                cell2 = g[r + 1][c]
                if cell == "." or cell == "B":
                    if cell2 == "." or cell2 == "B":
                        join(base, base + m)
                if cell == "." or cell == "R":
                    if cell2 == "." or cell2 == "R":
                        join(base + n * m, base + m + n * m)
    for qu in queries:
        rs, cs, re, ce = qu
        s = rs * m + cs
        cell = g[re][ce]
        if cell == "R":
            e = re * m + ce + n * m
        else:
            e = re * m + ce
        if find(s) == find(e):
            print("YES")
        else:
            print("NO")
