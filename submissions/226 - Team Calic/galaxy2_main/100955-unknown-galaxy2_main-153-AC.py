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
    INF = 10 ** 18
    W = 2 * N
    total = W * M

    def active(r, c, mode):
        ch = G[r][c]
        return ch == '.' or (ch == 'B' and mode == 0) or (ch == 'R' and mode == 1)

    # state id = ((c*N + r) << 1) | mode  -> a column is a contiguous id block
    adj = [None] * total
    for c in range(M):
        for r in range(N):
            for mode in (0, 1):
                if not active(r, c, mode):
                    continue
                sid = ((c * N + r) << 1) | mode
                nb = []
                if r > 0 and active(r - 1, c, mode):
                    nb.append(sid - 2)
                if r + 1 < N and active(r + 1, c, mode):
                    nb.append(sid + 2)
                if c > 0 and active(r, c - 1, mode):
                    nb.append(sid - W)
                if c + 1 < M and active(r, c + 1, mode):
                    nb.append(sid + W)
                if G[r][c] == '.':
                    nb.append(sid ^ 1)
                adj[sid] = nb

    # per query: start state, target states, columns
    S = [0] * Q
    T = [None] * Q
    cs = [0] * Q
    ct = [0] * Q
    for i in range(Q):
        sr, sc = start[i]
        er, ec = end[i]
        S[i] = ((sc * N + sr) << 1)          # blue mode (mode 0), start tile is normal
        base = (ec * N + er) << 1
        ch = G[er][ec]
        if ch == '.':
            T[i] = (base, base | 1)
        elif ch == 'B':
            T[i] = (base,)
        else:
            T[i] = (base | 1,)
        cs[i] = sc
        ct[i] = ec

    ans = [INF] * Q

    stack = [(0, M - 1, list(range(Q)))]
    while stack:
        l, r, qs = stack.pop()
        if not qs:
            continue
        mid = (l + r) >> 1
        lo = l * W
        hi = (r + 1) * W
        size = hi - lo

        # BFS from every active state of the mid column, restricted to [l, r]
        Ds = []
        for sid0 in range(mid * W, (mid + 1) * W):
            if adj[sid0] is None:
                continue
            D = [INF] * size
            D[sid0 - lo] = 0
            queue = [sid0]
            head = 0
            while head < len(queue):
                u = queue[head]
                head += 1
                du = D[u - lo] + 1
                for v in adj[u]:
                    if lo <= v < hi and D[v - lo] > du:
                        D[v - lo] = du
                        queue.append(v)
            Ds.append(D)

        left, right = [], []
        for q in qs:
            a, b = cs[q], ct[q]
            sl = S[q] - lo
            tl = [t - lo for t in T[q]]
            best = ans[q]
            for D in Ds:
                x = D[sl]
                if x < INF:
                    for t in tl:
                        y = D[t]
                        if x + y < best:
                            best = x + y
            ans[q] = best
            if a <= mid and b <= mid:
                if l < mid or a != b:
                    left.append(q)
            elif a > mid and b > mid:
                right.append(q)
            # else: crosses mid -> already exact, no recursion needed

        if l < r:
            if left:
                stack.append((l, mid, left))
            if right:
                stack.append((mid + 1, r, right))

    return ["YES" if ans[i] <= K[i] else "NO" for i in range(Q)]


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
