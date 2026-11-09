from operator import add, itemgetter
def solve(N: int, M: int, Q: int, G: list[str], start: list[tuple[int, int]], end: list[tuple[int, int]], K: list[int]) -> list[str]:
    """
    Return an array of Q strings, the i-th of which is "YES"
    if Big Ben can travel from start[i] to end[i] within K[i]
    seconds, and "NO" otherwise.

    N: the number of rows in the grid
    M: the number of columns in the grid
    Q: the number of queries
    G: the grid, where each tile is 'R', 'B', or '.'
    start: the (row, column) of the starting tile of each query
    end: the (row, column) of the ending tile of each query
    K: the maximum number of seconds allowed for each query
    """
    INF = 1 << 60
    W = 2 * N
    adj = [[] for _ in range(W * M)]
    valid = [False] * (W * M)
    for c in range(M):
        for r in range(N):
            t = G[r][c]
            for mode in (0, 1):
                if (t == 'B' and mode == 1) or (t == 'R' and mode == 0):
                    continue
                v = (c * N + r) * 2 + mode
                valid[v] = True
                nb = adj[v]
                if t == '.':
                    nb.append(v ^ 1)
                for rr, cc in ((r - 1, c), (r + 1, c), (r, c - 1), (r, c + 1)):
                    if 0 <= rr < N and 0 <= cc < M:
                        u = G[rr][cc]
                        if u == '.' or (u == 'B' and mode == 0) or (u == 'R' and mode == 1):
                            nb.append((cc * N + rr) * 2 + mode)

    def targets(r, c):
        t = G[r][c]
        base = (c * N + r) * 2
        if t == '.':
            return (base, base + 1)
        return (base + 1,) if t == 'R' else (base,)
    
    src = [(c * N + r) * 2 for r, c in start]
    dst = [targets(r, c) for r, c in end]
    best = [INF] * Q
    d = [INF] * (W * M)
    
    def bfs(source, l, r):
        lo, hi = l * W, (r + 1) * W
        d[lo:hi] = [INF] * (hi - lo)
        if l > 0:
            d[lo - W:lo] = [-1] * W
        if r < M - 1:
            d[hi:hi + W] = [-1] * W
        dist, graph = d, adj
        dist[source] = 0
        frontier = [source]
        k = 0
        while frontier:
            k += 1
            nxt = []
            push = nxt.append
            for u in frontier:
                for v in graph[u]:
                    if dist[v] > k:
                        dist[v] = k
                        push(v)
            frontier = nxt
    
    stack = [(0, M - 1, list(range(Q)))]
    while stack:
        l, r, qs = stack.pop()
        if not qs:
            continue
        mid = (l + r) // 2
        portals = [p for p in range(mid * W, (mid + 1) * W) if valid[p]]
        starts = {}
        for q in qs:
            starts.setdefault(src[q], []).append(q)
        if len(starts) <= len(portals):
            for s0, group in starts.items():
                bfs(s0, l, r)
                for q in group:
                    cand = min(d[t] for t in dst[q])
                    if cand < best[q]:
                        best[q] = cand
            continue
        points = sorted({v for q in qs for v in (src[q],) + dst[q]})
        getter = itemgetter(*points) if len(points) > 1 else (lambda arr, p=points[0]: (arr[p],))
        gathered = []
        for p in portals:
            bfs(p, l, r)
            gathered.append(getter(d))
        if gathered:
            row = dict(zip(points, zip(*gathered)))
            for q in qs:
                ts = dst[q]
                to_end = row[ts[0]] if len(ts) == 1 else tuple(map(min, row[ts[0]], row[ts[1]]))
                cand = min(map(add, row[src[q]], to_end))
                if cand < best[q]:
                    best[q] = cand
        left, right = [], []
        for q in qs:
            a, b = start[q][1], end[q][1]
            if a < mid and b < mid:
                left.append(q)
            elif a > mid and b > mid:
                right.append(q)
        stack.append((l, mid - 1, left))
        stack.append((mid + 1, r, right))
    return ["YES" if best[q] <= K[q] else "NO" for q in range(Q)]

def main():
    T = int(input())
    for _ in range(T):
        N, M, Q = map(int, input().split())
        G = []
        for _ in range(N):
            G.append(input())
        start, end, K = [], [], []
        for _ in range(Q):
            start_row, start_col, end_row, end_col, k = map(int, input().split())
            start.append((start_row, start_col))
            end.append((end_row, end_col))
            K.append(k)
        for s in solve(N, M, Q, G, start, end, K):
            print(s)

if __name__ == '__main__':
    main()
