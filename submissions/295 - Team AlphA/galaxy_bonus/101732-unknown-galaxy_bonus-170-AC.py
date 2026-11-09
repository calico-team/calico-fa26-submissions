t = int(input())
for _ in range(t):
    n, m, q = map(int, input().split())
    grid = [input().strip() for _ in range(n)]
    parent = list(range(2 * n * m))
    size = [1] * (2 * n * m)

    def find(x):
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x

    def union(a, b):
        a = find(a)
        b = find(b)
        if a == b:
            return
        if size[a] < size[b]:
            a, b = b, a
        parent[b] = a
        size[a] += size[b]

    def get_id(r, c, mode):
        return mode * n * m + r * m + c

    for r in range(n):
        for c in range(m):
            cell = grid[r][c]
            if cell == ".":
                union(get_id(r, c, 0), get_id(r, c, 1))
            for dr, dc in [(0, 1), (1, 0)]:
                nr = r + dr
                nc = c + dc
                if nr >= n or nc >= m:
                    continue
                other = grid[nr][nc]
                if cell != "R" and other != "R":
                    union(get_id(r, c, 0), get_id(nr, nc, 0))
                if cell != "B" and other != "B":
                    union(get_id(r, c, 1), get_id(nr, nc, 1))
    for _ in range(q):
        sr, sc, er, ec = map(int, input().split())
        start = get_id(sr, sc, 0)
        dest = grid[er][ec]
        if dest == ".":
            possible = find(start) == find(get_id(er, ec, 0)) or find(start) == find(
                get_id(er, ec, 1)
            )
        elif dest == "B":
            possible = find(start) == find(get_id(er, ec, 0))
        else:
            possible = find(start) == find(get_id(er, ec, 1))
        print("YES" if possible else "NO")
