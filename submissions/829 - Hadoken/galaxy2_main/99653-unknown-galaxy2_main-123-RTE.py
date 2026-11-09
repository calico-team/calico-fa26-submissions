import sys
from collections import deque

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
    NMererer = N * M
   
    adjererer = [[] for _ in range(2 * NMererer)]
    
   
    for r in range(N):
        for c in range(M):
            cellerer = G[r][c]
            idx_b = 0 * NMererer + r * M + c
            idx_r = 1 * NMererer + r * M + c
            
            
            if cellerer == '.':
                adjererer[idx_b].append((idx_r, c))
                adjererer[idx_r].append((idx_b, c))
                
            for dr, dc in [(0, 1), (1, 0)]:
                nr, nc = r + dr, c + dc
                if nr < N and nc < M:
                    ncell = G[nr][nc]
                    if cellerer in ('.', 'B') and ncell in ('.', 'B'):
                        nidx_b = 0 * NMererer + nr * M + nc
                        adjererer[idx_b].append((nidx_b, nc))
                        adjererer[nidx_b].append((idx_b, c))       
                    if cellerer in ('.', 'R') and ncell in ('.', 'R'):
                        nidx_r = 1 * NMererer + nr * M + nc
                        adjererer[idx_r].append((nidx_r, nc))
                        adjererer[nidx_r].append((idx_r, c))
    answererer = [float('inf')] * Q
    def solve_dc_function(L: int, R: int, active_queries: list[int]):
        if L > R or not active_queries:
            return 
        mid = (L + R) // 2
        dists = []
        for r in range(N):
            for mode in (0, 1):
                start_idx = mode * NMererer + r * M + mid
                dist = [-1] * (2 * NMererer)
                q = deque([start_idx])
                dist[start_idx] = 0
                while q:
                    u = q.popleft()
                    d = dist[u]
                    for v, vc in adjererer[u]:
                        if L <= vc <= R and dist[v] == -1:
                            dist[v] = d + 1
                            q.append(v)
                dists.append(dist)

        left_queries = []
        right_queries = [] 
        for q_idx in active_queries:
            rs, cs = start[q_idx]
            re, ce = end[q_idx]
            s_idxfgh = 0 * NMererer + rs * M + cs
            e_idx_b_erer = 0 * NMererer + re * M + ce
            e_idx_rasdas = 1 * NMererer + re * M + ce       
            responder = answererer[q_idx]
            for d_arradf in dists:
                d1 = d_arradf[s_idxfgh]
                if d1 == -1:
                    continue   
                d2_b_var = d_arradf[e_idx_b_erer]
                d2_r_var = d_arradf[e_idx_rasdas]
                d2 = -1
                if d2_b_var != -1 and d2_r_var != -1:
                    d2 = d2_b_var if d2_b_var < d2_r_var else d2_r_var
                elif d2_b_var != -1:
                    d2 = d2_b_var
                elif d2_r_var != -1:
                    d2 = d2_r_var              
                if d2 != -1:
                    total = d1 + d2
                    if total < responder:
                        responder = total             
            answererer[q_idx] = responder
            if cs < mid and ce < mid:
                left_queries.append(q_idx)
            elif cs > mid and ce > mid:
                right_queries.append(q_idx)

        solve_dc_function(L, mid - 1, left_queries)
        solve_dc_function(mid + 1, R, right_queries)
    solve_dc_function(0, M - 1, list(range(Q)))
    outputerer = []
    for i in range(Q):
        if answererer[i] <= K[i]:
            outputerer.append("YES")
        else:
            outputerer.append("NO")
    return outputerer
def main():
    T = int(input())
    for _ in range(T):
        N, M, Q = map(int, input().split())
        G = []
        for nope in range(N):
            G.append(input())
        start, end, K = [], [], []
        for nope in range(Q):
            start_row, start_col, end_row, end_col, k = map(int, input().split())
            start.append((start_row, start_col))
            end.append((end_row, end_col))
            K.append(k)
        for s in solve(N, M, Q, G, start, end, K):
            print(s)
if __name__ == '__main__':
    main()