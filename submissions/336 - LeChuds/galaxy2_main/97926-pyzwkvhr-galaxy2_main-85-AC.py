import sys

input = sys.stdin.readline


def solve(N: int, M: int, Q: int, G: list[str], start: list[tuple[int, int]], end: list[tuple[int, int]], K: list[int]) -> list[str]:
    S = N * M * 2
    INF = 1 << 40

    ok = [False] * S
    for c in range(M):
        for r in range(N):
            i = (c * N + r) * 2
            ok[i] = G[r][c] != 'R'
            ok[i + 1] = G[r][c] != 'B'

    nb = [[] for _ in range(S)]
    for c in range(M):
        for r in range(N):
            for m in range(2):
                i = (c * N + r) * 2 + m
                if not ok[i]:
                    continue
                if G[r][c] == '.':
                    nb[i].append(i ^ 1)
                for rr, cc in ((r - 1, c), (r + 1, c), (r, c - 1), (r, c + 1)):
                    if 0 <= rr < N and 0 <= cc < M and ok[(cc * N + rr) * 2 + m]:
                        nb[i].append((cc * N + rr) * 2 + m)

    s_state = [(c * N + r) * 2 for r, c in start]
    t_state = [(c * N + r) * 2 for r, c in end]
    best = [INF] * Q
    dist = [INF] * (S + 2)

    def bfs(src, limit, goal):
        dist[src] = 0
        seen = [src]
        layer = [src]
        d = 0
        while layer and d < limit and dist[goal] == INF and dist[goal + 1] == INF:
            d += 1
            nxt = []
            for x in layer:
                for y in nb[x]:
                    if dist[y] == INF:
                        dist[y] = d
                        nxt.append(y)
            seen += nxt
            layer = nxt
        return seen

    def go(lo, hi, qs):
        if not qs:
            return
        mid = (lo + hi) // 2

        walls = []
        for c in (lo - 1, hi + 1):
            if 0 <= c < M:
                walls += range(c * N * 2, (c + 1) * N * 2)
        for x in walls:
            dist[x] = -1

        if len(qs) <= 100:
            for qi in qs:
                t = t_state[qi]
                seen = bfs(s_state[qi], K[qi], t)
                best[qi] = min(dist[t], dist[t + 1], best[qi])
                for x in seen:
                    dist[x] = INF
        else:
            todo = [qi for qi in qs if abs(start[qi][1] - mid) + abs(end[qi][1] - mid) <= K[qi]]
            limit = max([K[qi] for qi in todo], default=0)
            for src in range(mid * N * 2, (mid + 1) * N * 2):
                if ok[src] and todo:
                    seen = bfs(src, limit, S)
                    for qi in todo:
                        s = s_state[qi]
                        t = t_state[qi]
                        best[qi] = min(best[qi], dist[s] + dist[t], dist[s] + dist[t + 1])
                    for x in seen:
                        dist[x] = INF

        for x in walls:
            dist[x] = INF

        if len(qs) > 100:
            go(lo, mid - 1, [qi for qi in qs if best[qi] > K[qi] and start[qi][1] < mid and end[qi][1] < mid])
            go(mid + 1, hi, [qi for qi in qs if best[qi] > K[qi] and start[qi][1] > mid and end[qi][1] > mid])

    go(0, M - 1, [i for i in range(Q) if abs(start[i][0] - end[i][0]) + abs(start[i][1] - end[i][1]) <= K[i]])
    return ["YES" if best[i] <= K[i] else "NO" for i in range(Q)]


def main():
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
