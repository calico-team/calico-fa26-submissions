import sys
input = sys.stdin.readline

INF = float("inf")

def solve(N, M, grid, queries):
    def active(r, c, m):
        return grid[r][c] == "." or grid[r][c] == "BR"[m]

    def state(r, c, m):
        return (c * N + r) * 2 + m

    adj = [[] for _ in range(N * M * 2)]
    for r in range(N):
        for c in range(M):
            for m in (0, 1):
                if active(r, c, m):
                    for nr, nc in ((r + 1, c), (r, c + 1)):
                        if nr < N and nc < M and active(nr, nc, m):
                            adj[state(r, c, m)].append(state(nr, nc, m))
                            adj[state(nr, nc, m)].append(state(r, c, m))
            if grid[r][c] == ".":  # spin
                adj[state(r, c, 0)].append(state(r, c, 1))
                adj[state(r, c, 1)].append(state(r, c, 0))

    best = [INF] * len(queries)
    start = [state(rs, cs, 0) for rs, cs, re, ce, k in queries]
    end = [state(re, ce, 0) for rs, cs, re, ce, k in queries]

    def solve_range(l, r, qids):
        if l > r or not qids:
            return
        lo, hi = l * N * 2, (r + 1) * N * 2
        mid = (l + r) // 2
        sources = [state(row, mid, m) for row in range(N) for m in (0, 1) if active(row, mid, m)]
        local = [[w - lo for w in adj[u] if lo <= w < hi] for u in range(lo, hi)]

        starts = set(start[i] for i in qids)
        if len(starts) <= len(sources):
            for s in starts:
                dist = bfs(local, s - lo)
                for i in qids:
                    if start[i] == s:
                        best[i] = min(best[i], dist[end[i] - lo], dist[end[i] + 1 - lo])
            return

        for v in sources:
            dist = bfs(local, v - lo)
            for i in qids:
                d = dist[start[i] - lo] + min(dist[end[i] - lo], dist[end[i] + 1 - lo])
                if d < best[i]:
                    best[i] = d
        solve_range(l, mid - 1, [i for i in qids if queries[i][1] < mid and queries[i][3] < mid])
        solve_range(mid + 1, r, [i for i in qids if queries[i][1] > mid and queries[i][3] > mid])

    def bfs(graph, src):
        dist = [INF] * len(graph)
        dist[src] = 0
        frontier = [src]
        while frontier:
            nxt = []
            for u in frontier:
                for w in graph[u]:
                    if dist[w] == INF:
                        dist[w] = dist[u] + 1
                        nxt.append(w)
            frontier = nxt
        return dist

    solve_range(0, M - 1, list(range(len(queries))))
    return ["YES" if best[i] <= q[4] else "NO" for i, q in enumerate(queries)]


data = sys.stdin.read().split()
pos = 0
out = []
for _ in range(int(data[0])):
    N, M, Q = map(int, data[pos + 1:pos + 4])
    grid = data[pos + 4:pos + 4 + N]
    pos += 3 + N
    queries = []
    for _ in range(Q):
        queries.append(tuple(map(int, data[pos + 1:pos + 6])))
        pos += 5
    out += solve(N, M, grid, queries)
print("\n".join(out))