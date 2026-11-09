
import sys
import heapq


def solve():
    input = sys.stdin.buffer.readline
    T = int(input())

    output = []

    for _ in range(T):
        N, M, Q = map(int, input().split())
        grid = [input().decode().strip() for _ in range(N)]

        V = 2 * N * M

        # Mode 0 = blue, mode 1 = red.
        # A state exists only if its tile is active in that mode.
        adj = [None] * V

        def node(r, c, mode):
            return (r * M + c) * 2 + mode

        def active(ch, mode):
            return ch == '.' or (ch == 'B' and mode == 0) or (
                ch == 'R' and mode == 1
            )

        for r in range(N):
            for c in range(M):
                ch = grid[r][c]
                for mode in range(2):
                    if active(ch, mode):
                        adj[node(r, c, mode)] = {}

        def add_edge(u, v, w=1):
            adj[u][v] = w
            adj[v][u] = w

        for r in range(N):
            for c in range(M):
                ch = grid[r][c]

                if ch == '.':
                    add_edge(node(r, c, 0), node(r, c, 1))

                for dr, dc in ((1, 0), (0, 1)):
                    nr, nc = r + dr, c + dc
                    if nr >= N or nc >= M:
                        continue

                    nch = grid[nr][nc]

                    for mode in range(2):
                        if active(ch, mode) and active(nch, mode):
                            add_edge(
                                node(r, c, mode),
                                node(nr, nc, mode)
                            )

        # Separator-first column elimination order.
        columns = []
        stack = [(0, M)]

        while stack:
            left, right = stack.pop()
            if left >= right:
                continue

            mid = (left + right) // 2
            columns.append(mid)

            stack.append((mid + 1, right))
            stack.append((left, mid))

        # Upward graph and its reverse.
        up = [[] for _ in range(V)]
        rev = [[] for _ in range(V)]

        # Eliminate all active states in each column.
        for c in columns:
            for r in range(N):
                for mode in range(2):
                    v = node(r, c, mode)

                    if adj[v] is None:
                        continue

                    neighbors = list(adj[v].items())

                    # Add shortcuts between all remaining neighbors.
                    for i in range(len(neighbors)):
                        u, du = neighbors[i]

                        for j in range(i + 1, len(neighbors)):
                            w, dw = neighbors[j]
                            nd = du + dw

                            old = adj[u].get(w)

                            if old is None or nd < old:
                                adj[u][w] = nd
                                adj[w][u] = nd

                    # Store upward edges.
                    for u, d in neighbors:
                        up[v].append((u, d))
                        rev[u].append((v, d))
                        adj[u].pop(v, None)

                    adj[v] = None

        def shortest(start, targets):
            # Bidirectional Dijkstra:
            # forward uses upward edges;
            # backward uses reversed upward edges.
            dist_f = {start: 0}
            dist_b = {}
            pq_f = [(0, start)]
            pq_b = []

            for t in targets:
                dist_b[t] = 0
                heapq.heappush(pq_b, (0, t))

            best = float('inf')

            while pq_f and pq_b:
                if pq_f[0][0] + pq_b[0][0] >= best:
                    break

                if pq_f[0][0] <= pq_b[0][0]:
                    d, u = heapq.heappop(pq_f)

                    if d != dist_f.get(u):
                        continue

                    if u in dist_b:
                        best = min(best, d + dist_b[u])

                    for v, w in up[u]:
                        nd = d + w

                        if nd < dist_f.get(v, float('inf')):
                            dist_f[v] = nd
                            heapq.heappush(pq_f, (nd, v))

                            if v in dist_b:
                                best = min(best, nd + dist_b[v])

                else:
                    d, u = heapq.heappop(pq_b)

                    if d != dist_b.get(u):
                        continue

                    if u in dist_f:
                        best = min(best, d + dist_f[u])

                    for v, w in rev[u]:
                        nd = d + w

                        if nd < dist_b.get(v, float('inf')):
                            dist_b[v] = nd
                            heapq.heappush(pq_b, (nd, v))

                            if v in dist_f:
                                best = min(best, nd + dist_f[v])

            return best

        for _ in range(Q):
            rs, cs, re, ce, K = map(int, input().split())

            start = node(rs, cs, 0)

            targets = []
            for mode in range(2):
                if active(grid[re][ce], mode):
                    targets.append(node(re, ce, mode))

            if (rs == re and cs == ce):
                output.append("YES")
                continue

            distance = shortest(start, targets)

            output.append("YES" if distance <= K else "NO")

    sys.stdout.write("\n".join(output))


if __name__ == "__main__":
    solve()

