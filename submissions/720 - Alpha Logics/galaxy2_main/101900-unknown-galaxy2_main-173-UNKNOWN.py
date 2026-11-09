from collections import deque
from array import array

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
    # YOUR CODE HERE

    V = 2 * N * M
    adj = [[] for _ in range(V)]

    def node_id(mode, r, c):
        return (mode * N + r) * M + c

    def running(r, c, mode):
        ch = G[r][c]
        return ch == '.' or (mode == 0 and ch == 'B') or (mode == 1 and ch == 'R')

    for r in range(N):
        for c in range(M):
            for mode in range(2):
                if not running(r, c, mode):
                    continue

                u = node_id(mode, r, c)

                if c + 1 < M and running(r, c + 1, mode):
                    v = node_id(mode, r, c + 1)
                    adj[u].append(v)
                    adj[v].append(u)

                if r + 1 < N and running(r + 1, c, mode):
                    v = node_id(mode, r + 1, c)
                    adj[u].append(v)
                    adj[v].append(u)

            if G[r][c] == '.':
                u = node_id(0, r, c)
                v = node_id(1, r, c)
                adj[u].append(v)
                adj[v].append(u)

    data = [None] * M

    def made(lo, hi):
        if lo > hi:
            return

        mid = (lo + hi) // 2
        width = hi - lo + 1
        length = 2 * N * width

        sources = []

        for mode in range(2):
            for r in range(N):
                if running(r, mid, mode):
                    sources.append(node_id(mode, r, mid))

        rows = []

        for src in sources:
            dist = array('i', [-1]) * length

            group = src // M
            idx = group * width + mid - lo
            dist[idx] = 0

            q = deque([src])

            while q:
                u = q.popleft()

                group_u = u // M
                col_u = u % M
                du = dist[group_u * width + col_u - lo]

                nd = du + 1

                for v in adj[u]:
                    col_v = v % M

                    if col_v < lo or col_v > hi:
                        continue

                    group_v = v // M
                    vi = group_v * width + col_v - lo

                    if dist[vi] == -1:
                        dist[vi] = nd
                        q.append(v)

            rows.append((src, dist))

        data[mid] = (lo, hi, rows)

        made(lo, mid - 1)
        made(mid + 1, hi)

    made(0, M - 1)

    ans = []

    for qi in range(Q):
        sr, sc = start[qi]
        er, ec = end[qi]
        limit = K[qi]

        best = limit + 1

        x = node_id(0, sr, sc)
        targets = []

        if running(er, ec, 0):
            targets.append(node_id(0, er, ec))

        if running(er, ec, 1):
            targets.append(node_id(1, er, ec))

        lo, hi = 0, M - 1

        while lo <= hi:
            mid = (lo + hi) // 2

            node_lo, node_hi, rows = data[mid]
            width = node_hi - node_lo + 1

            gx = x // M
            ix = gx * width + sc - node_lo

            for src, dist in rows:
                dx = dist[ix]

                if dx == -1:
                    continue

                for y in targets:
                    gy = y // M
                    iy = gy * width + ec - node_lo

                    dy = dist[iy]

                    if dy != -1 and dx + dy < best:
                        best = dx + dy

                if best <= limit:
                    break

            if best <= limit:
                break

            if sc == mid or ec == mid:
                break

            if sc < mid and ec < mid:
                hi = mid - 1
            elif sc > mid and ec > mid:
                lo = mid + 1
            else:
                break

        ans.append("YES" if best <= limit else "NO")

    return ans

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
