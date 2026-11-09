import sys

def solve(N: int, M: int, Q: int, G: list[str], start: list[tuple[int, int]], end: list[tuple[int, int]], K: list[int]) -> list[str]:
    def active(r, c, mode):
        return G[r][c] == '.' or G[r][c] == 'BR'[mode]

    W = 2 * N
    adj = [[] for _ in range(M * W)]
    for c in range(M):
        for r in range(N):
            for mode in (0, 1):
                if not active(r, c, mode):
                    continue
                u = (c * N + r) * 2 + mode
                if G[r][c] == '.':
                    adj[u].append(u ^ 1)
                for nr, nc in ((r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1)):
                    if 0 <= nr < N and 0 <= nc < M and active(nr, nc, mode):
                        adj[u].append((nc * N + nr) * 2 + mode)

    INF = 10**9 + 1
    ans = [0 if sr == er and sc == ec else INF for (sr, sc), (er, ec) in zip(start, end)]
    stack = [(0, M - 1, [i for i in range(Q) if ans[i] == INF])]

    while stack:
        lo, hi, qs = stack.pop()
        if not qs or lo > hi:
            continue
        mid = (lo + hi) // 2
        base = lo * W
        size = (hi - lo + 1) * W

        # BFS from every active state of the mid column, inside [lo, hi] only.
        # one padding column on each side is pre-marked as visited, so no range check is needed
        off = base - W
        tables = []
        for u in range(mid * W, (mid + 1) * W):
            if not adj[u]:
                continue
            d = [-1] * W + [INF] * size + [-1] * W
            d[u - off] = 0
            frontier = [u]
            step = 0
            while frontier:
                step += 1
                nxt = []
                for x in frontier:
                    for y in adj[x]:
                        if d[y - off] == INF:
                            d[y - off] = step
                            nxt.append(y)
                frontier = nxt
            tables.append(d[W:W + size])

        left, right = [], []
        for i in qs:
            sr, sc = start[i]
            er, ec = end[i]
            s = (sc * N + sr) * 2 - base
            e = (ec * N + er) * 2 - base
            best = ans[i]
            for tbl in tables:
                d = tbl[s] + (tbl[e] if tbl[e] < tbl[e + 1] else tbl[e + 1])
                if d < best:
                    best = d
            ans[i] = best
            if sc < mid and ec < mid:
                left.append(i)
            elif sc > mid and ec > mid:
                right.append(i)

        if left:
            stack.append((lo, mid - 1, left))
        if right:
            stack.append((mid + 1, hi, right))

    return ["YES" if ans[i] <= K[i] else "NO" for i in range(Q)]


def main():
    input = sys.stdin.readline
    T = int(input())
    for _ in range(T):
        N, M, Q = map(int, input().split())
        G = []
        for _ in range(N):
            G.append(input().strip())
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