import sys
from collections import deque

def solve_la():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    iterator = iter(input_data)
    num_test_cases = int(next(iterator))
    global_output = []
    
    for _ in range(num_test_cases):
        N = int(next(iterator))
        M = int(next(iterator))
        Q = int(next(iterator))
        grid = [next(iterator) for _ in range(N)]
        
        S = N * M * 2
        adj = [[] for _ in range(S)]
        
        for r in range(N):
            row_str = grid[r]
            for c in range(M):
                char = row_str[c]
                u0 = (r * M + c) * 2
                u1 = u0 + 1
                if char == '.':
                    adj[u0].append(u1)
                    adj[u1].append(u0)
                    modes = (0, 1)
                elif char == 'R':
                    modes = (1,)
                elif char == 'B':
                    modes = (0,)
                else:
                    modes = ()
                
                for m in modes:
                    u = u0 + m
                    for dr, dc in ((-1, 0), (1, 0), (0, -1), (0, 1)):
                        nr, nc = r + dr, c + dc
                        if 0 <= nr < N and 0 <= nc < M:
                            nchar = grid[nr][nc]
                            if nchar == '.' or (nchar == 'R' and m == 1) or (nchar == 'B' and m == 0):
                                adj[u].append((nr * M + nc) * 2 + m)
        
        queries = []
        for i in range(Q):
            r1 = int(next(iterator))
            c1 = int(next(iterator))
            r2 = int(next(iterator))
            c2 = int(next(iterator))
            K = int(next(iterator))
            queries.append((r1, c1, r2, c2, K, i))
            
        ans_dist = [10**15] * Q
        dist_array = [-1] * S
        
        def dandq(L, R, curr_queries):
            if L > R or not curr_queries:
                return
            
            if len(curr_queries) <= 2 * N:
                for q_tuple in curr_queries:
                    r1, c1, r2, c2, K, idx = q_tuple
                    start_state = (r1 * M + c1) * 2
                    t_state_0 = (r2 * M + c2) * 2
                    t_state_1 = t_state_0 + 1
                    
                    q = deque([start_state])
                    dist_array[start_state] = 0
                    visited_nodes = [start_state]
                    
                    while q:
                        u = q.popleft()
                        d = dist_array[u]
                        for v in adj[u]:
                            if dist_array[v] == -1:
                                dist_array[v] = d + 1
                                q.append(v)
                                visited_nodes.append(v)
                                
                    min_d = 10**15
                    if dist_array[t_state_0] != -1: min_d = min(min_d, dist_array[t_state_0])
                    if dist_array[t_state_1] != -1: min_d = min(min_d, dist_array[t_state_1])
                    ans_dist[idx] = min_d
                    
                    for node in visited_nodes:
                        dist_array[node] = -1
                return

            mid = (L + R) // 2
            
            mid_queries = []
            next_left = []
            next_right = []
            for q_tuple in curr_queries:
                r1, c1, r2, c2, K, idx = q_tuple
                if min(c1, c2) <= mid <= max(c1, c2):
                    mid_queries.append(q_tuple)
                elif max(c1, c2) < mid:
                    next_left.append(q_tuple)
                else:
                    next_right.append(q_tuple)
            
            if mid_queries:
                for r_mid in range(N):
                    for m_mid in (0, 1):
                        start_state = (r_mid * M + mid) * 2 + m_mid
                        
                        q = deque([start_state])
                        dist_array[start_state] = 0
                        visited_nodes = [start_state]
                        
                        while q:
                            u = q.popleft()
                            d = dist_array[u]
                            for v in adj[u]:
                                if dist_array[v] == -1:
                                    dist_array[v] = d + 1
                                    q.append(v)
                                    visited_nodes.append(v)
                                    
                        for r1, c1, r2, c2, K, idx in mid_queries:
                            s_state = (r1 * M + c1) * 2
                            t_state_0 = (r2 * M + c2) * 2
                            t_state_1 = t_state_0 + 1
                            
                            if dist_array[s_state] != -1:
                                d1 = dist_array[s_state]
                                d2_0 = dist_array[t_state_0]
                                d2_1 = dist_array[t_state_1]
                                
                                if d2_0 != -1 and d1 + d2_0 < ans_dist[idx]:
                                    ans_dist[idx] = d1 + d2_0
                                if d2_1 != -1 and d1 + d2_1 < ans_dist[idx]:
                                    ans_dist[idx] = d1 + d2_1
                                    
                        for node in visited_nodes:
                            dist_array[node] = -1
                            
            dandq(L, mid - 1, next_left)
            dandq(mid + 1, R, next_right)
            
        dandq(0, M - 1, queries)
        
        for i in range(Q):
            r1, c1, r2, c2, K, idx = queries[i]
            if ans_dist[i] <= K:
                global_output.append("YES")
            else:
                global_output.append("NO")
                
    sys.stdout.write('\n'.join(global_output) + '\n')

if __name__ == '__main__':
    solve_la()
