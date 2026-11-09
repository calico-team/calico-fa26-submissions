from collections import deque

def solve(N: int, M: int, Q: int, G: list[str], queries: list[tuple[int, int, int, int, int]]) -> list[str]:
    adj = [[] for _ in range(2 * N * M)]
    for r in range(N):
        for c in range(M):
            ch = G[r][c]
            b_idx = r * M + c
            r_idx = N * M + b_idx

            if ch == '.':
                adj[b_idx].append(r_idx)
                adj[r_idx].append(b_idx)

            for dr, dc in ((-1, 0), (1, 0), (0, -1), (0, 1)):
                nr, nc = r + dr, c + dc
                if 0 <= nr < N and 0 <= nc < M:
                    nch = G[nr][nc]
                    nb = nr * M + nc
                    nr_idx = N * M + nb
                    if nch == '.' or nch == 'B':
                        adj[b_idx].append(nb)
                    if nch == '.' or nch == 'R':
                        adj[r_idx].append(nr_idx)

    memo = {}
    ans = []
    for sr, sc, tr, tc, K in queries:
        start_state = sr * M + sc
        if start_state not in memo:
            dist = [-1] * (2 * N * M)
            dist[start_state] = 0
            q = deque([start_state])
            while q:
                u = q.popleft()
                d = dist[u] + 1
                for v in adj[u]:
                    if dist[v] == -1:
                        dist[v] = d
                        q.append(v)
            memo[start_state] = dist

        d_arr = memo[start_state]
        tb = tr * M + tc
        tr_idx = N * M + tb
        d1 = d_arr[tb]
        d2 = d_arr[tr_idx]

        min_d = -1
        if d1 != -1 and d2 != -1:
            min_d = d1 if d1 < d2 else d2
        elif d1 != -1:
            min_d = d1
        elif d2 != -1:
            min_d = d2

        if min_d != -1 and min_d <= K:
            ans.append("YES")
        else:
            ans.append("NO")

    return ans

def main():
    first = input().split()
    if not first:
        return
    T = int(first[0])
    for _ in range(T):
        N, M, Q = map(int, input().split())
        G = [input().strip() for _ in range(N)]
        queries = []
        for _ in range(Q):
            sr, sc, tr, tc, K = map(int, input().split())
            queries.append((sr, sc, tr, tc, K))
        print('\n'.join(solve(N, M, Q, G, queries)))

if _name_ == '_main_':
    main()