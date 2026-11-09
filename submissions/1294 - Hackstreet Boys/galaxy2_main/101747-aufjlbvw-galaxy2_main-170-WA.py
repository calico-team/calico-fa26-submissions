
import heapq

def solve(N: int, M: int, Q: int, G: list[str],
          start: list[tuple[int, int]],
          end: list[tuple[int, int]],
          limits: list[int]) -> list[str]:

    V = N * M
    S = 2 * V
    INF = 10**18

    adj = [{} for _ in range(S)]

    # State 0: Blue mode
    # State 1: Red mode

    def active(ch, mode):
        return ch == '.' or (mode == 0 and ch == 'B') or (mode == 1 and ch == 'R')

    # Construct the state graph.
    for r in range(N):
        for c in range(M):
            u = r * M + c

            for mode in range(2):
                if not active(G[r][c], mode):
                    continue

                x = mode * V + u

                if r + 1 < N and active(G[r + 1][c], mode):
                    y = mode * V + (r + 1) * M + c
                    adj[x][y] = 1
                    adj[y][x] = 1

                if c + 1 < M and active(G[r][c + 1], mode):
                    y = mode * V + r * M + c + 1
                    adj[x][y] = 1
                    adj[y][x] = 1

            # Spin action on normal tiles.
            if G[r][c] == '.':
                x = u
                y = V + u
                adj[x][y] = 1
                adj[y][x] = 1

    # Elimination order: column by column.
    # This exploits the small grid height.
    order = []

    for c in range(M):
        for r in range(N):
            u = r * M + c
            order.append(u)
            order.append(V + u)

    # Build contraction hierarchy.
    rank = [0] * S

    for i, u in enumerate(order):
        rank[u] = i

    upward = [[] for _ in range(S)]

    for u in order:
        neighbors = list(adj[u].items())

        # Save upward edges.
        upward[u] = neighbors

        # Add shortcuts between remaining neighbors.
        ln = len(neighbors)

        for i in range(ln):
            a, wa = neighbors[i]

            for j in range(i + 1, ln):
                b, wb = neighbors[j]

                nd = wa + wb

                if nd < adj[a].get(b, INF):
                    adj[a][b] = nd
                    adj[b][a] = nd

        # Remove the contracted vertex.
        for v, w in neighbors:
            adj[v].pop(u, None)

        adj[u].clear()

    # Shortest path query on the upward graph.
    def reachable(source, targets, K):

        dist_a = {source: 0}
        dist_b = {}

        heap_a = [(0, source)]
        heap_b = []

        for t in targets:
            if t not in dist_b:
                dist_b[t] = 0
                heapq.heappush(heap_b, (0, t))

        best = INF

        while heap_a and heap_b:

            # Remove outdated entries.
            while heap_a and dist_a.get(heap_a[0][1], INF) != heap_a[0][0]:
                heapq.heappop(heap_a)

            while heap_b and dist_b.get(heap_b[0][1], INF) != heap_b[0][0]:
                heapq.heappop(heap_b)

            if not heap_a or not heap_b:
                break

            da = heap_a[0][0]
            db = heap_b[0][0]

            if da + db >= best:
                break

            # Expand the smaller frontier.
            if da <= db:
                d, u = heapq.heappop(heap_a)

                if u in dist_b:
                    best = min(best, d + dist_b[u])

                for v, w in upward[u]:
                    nd = d + w

                    if nd < dist_a.get(v, INF):
                        dist_a[v] = nd
                        heapq.heappush(heap_a, (nd, v))

                        if v in dist_b:
                            best = min(best, nd + dist_b[v])

            else:
                d, u = heapq.heappop(heap_b)

                if u in dist_a:
                    best = min(best, d + dist_a[u])

                for v, w in upward[u]:
                    nd = d + w

                    if nd < dist_b.get(v, INF):
                        dist_b[v] = nd
                        heapq.heappush(heap_b, (nd, v))

                        if v in dist_a:
                            best = min(best, nd + dist_a[v])

            if best <= K:
                return True

        return best <= K

    answers = []

    for i in range(Q):
        sr, sc = start[i]
        er, ec = end[i]
        K = limits[i]

        source = sr * M + sc
        destination = er * M + ec

        # Initial mode is blue.
        # Destination can be reached in either valid mode.
        targets = []

        ch = G[er][ec]

        if ch == '.' or ch == 'B':
            targets.append(destination)

        if ch == '.' or ch == 'R':
            targets.append(V + destination)

        if not targets:
            answers.append("NO")
            continue

        if source == destination:
            answers.append("YES")
            continue

        if reachable(source, targets, K):
            answers.append("YES")
        else:
            answers.append("NO")

    return answers


def main():
    T = int(input())

    for _ in range(T):
        N, M, Q = map(int, input().split())

        G = []
        for _ in range(N):
            G.append(input())

        start, end, limits = [], [], []

        for _ in range(Q):
            start_row, start_col, end_row, end_col, K = map(int, input().split())

            start.append((start_row, start_col))
            end.append((end_row, end_col))
            limits.append(K)

        for ans in solve(N, M, Q, G, start, end, limits):
            print(ans)


if __name__ == '__main__':
    main()
