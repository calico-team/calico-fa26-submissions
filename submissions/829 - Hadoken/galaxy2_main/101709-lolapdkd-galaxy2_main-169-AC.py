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
    NM_points = N * M
    adjoint = [[] for _ in range(2 * NM_points)]
    for r in range(N):
        for c in range(M):
            cell = G[r][c]
            idx_b = 0 * NM_points + r * M + c
            idx_r = 1 * NM_points + r * M + c
        
            if cell == '.':
                adjoint[idx_b].append((idx_r, c))
                adjoint[idx_r].append((idx_b, c))
                
            for dr, dc in [(0, 1), (1, 0)]:
                nr, nc = r + dr, c + dc
                if nr < N and nc < M:
                    ncell = G[nr][nc]
                    
                    if cell in ('.', 'B') and ncell in ('.', 'B'):
                        nidx_b = 0 * NM_points + nr * M + nc
                        adjoint[idx_b].append((nidx_b, nc))
                        adjoint[nidx_b].append((idx_b, c))

                    if cell in ('.', 'R') and ncell in ('.', 'R'):
                        nidx_r = 1 * NM_points + nr * M + nc
                        adjoint[idx_r].append((nidx_r, nc))
                        adjoint[nidx_r].append((idx_r, c))

    answerer = [float('inf')] * Q
    
    dist_of_memoo = [[-1] * (2 * NM_points) for _ in range(2 * N)]
    visited_nodes = [[] for _ in range(2 * N)]
    
    def solve_dc_func(L: int, R: int, active_Queserie: list[int]):
        if L > R or not active_Queserie:
            return
            
        midpoint = (L + R) // 2
        
        for r in range(N):
            for mode in (0, 1):
                midpoint_idx = mode * N + r  
                start_node = mode * NM_points + r * M + midpoint
                
                q = deque([start_node])
                dist_of_memoo[midpoint_idx][start_node] = 0
                visited_nodes[midpoint_idx].append(start_node)
                while q:
                    u = q.popleft()
                    d = dist_of_memoo[midpoint_idx][u]       
                    for v, vc in adjoint[u]:
                        if L <= vc <= R and dist_of_memoo[midpoint_idx][v] == -1:
                            dist_of_memoo[midpoint_idx][v] = d + 1
                            visited_nodes[midpoint_idx].append(v)
                            q.append(v)

        left_queries_i = []
        right_queries_j = []
        
        for q_idx in active_Queserie:
            rs, cs = start[q_idx]
            re, ce = end[q_idx]





            

            s_node = 0 * NM_points + rs * M + cs
            e_node_b = 0 * NM_points + re * M + ce
            e_node_r = 1 * NM_points + re * M + ce
            
            repoonse = answerer[q_idx]
            
            for midpoint_idx in range(2 * N):
                d1 = dist_of_memoo[midpoint_idx][s_node]
                if d1 == -1:
                    continue
                    
                d2_b = dist_of_memoo[midpoint_idx][e_node_b]
                d2_r = dist_of_memoo[midpoint_idx][e_node_r]





                
                d2 = -1
                if d2_b != -1 and d2_r != -1:
                    d2 = d2_b if d2_b < d2_r else d2_r
                elif d2_b != -1:
                    d2 = d2_b
                elif d2_r != -1:
                    d2 = d2_r
                    
                if d2 != -1:
                    total = d1 + d2
                    if total < repoonse:
                        repoonse = total
                        
            answerer[q_idx] = repoonse
      
            if cs < midpoint and ce < midpoint:
                left_queries_i.append(q_idx)
            elif cs > midpoint and ce > midpoint:
                right_queries_j.append(q_idx)
        for midpoint_idx in range(2 * N):
            for node in visited_nodes[midpoint_idx]:
                dist_of_memoo[midpoint_idx][node] = -1
            visited_nodes[midpoint_idx].clear()
            
        solve_dc_func(L, midpoint - 1, left_queries_i)
        solve_dc_func(midpoint + 1, R, right_queries_j)

    solve_dc_func(0, M - 1, list(range(Q)))

    ouput = []
    for i in range(Q):
        if answerer[i] <= K[i]:
            ouput.append("YES")
        else:
            ouput.append("NO")  
    return ouput

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