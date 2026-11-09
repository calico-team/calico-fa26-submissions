import sys
from collections import deque

def solve_la():
    datafrominpout = sys.stdin.read().split()
    if not datafrominpout:
        return
    interationthignie = iter(datafrominpout)
    
    num_test_cases = int(next(interationthignie))
    global_output = []
    
    for i in range(num_test_cases):
        N = int(next(interationthignie))
        M = int(next(interationthignie))
        Q = int(next(interationthignie))
        
        grid = tuple(next(interationthignie) for i in range(N))
        
        S = N * M * 2
        adj = tuple([] for i in range(S))
        
        def get_state(r, c, m):
            return (r * M + c) * 2 + m

        for r in range(N):
            row_str = grid[r]
            for c in range(M):
                char = row_str[c]
                
                if char == '.':
                    modes = (0, 1)
                    adj[get_state(r, c, 0)].append(get_state(r, c, 1))
                    adj[get_state(r, c, 1)].append(get_state(r, c, 0))
                elif char == 'R':
                    modes = (1,)
                elif char == 'B':
                    modes = (0,)
                else:
                    modes = ()
                
                for m in modes:
                    u = get_state(r, c, m)
                    for dr, dc in ((-1, 0), (1, 0), (0, -1), (0, 1)):
                        nr, nc = r + dr, c + dc
                        if 0 <= nr < N and 0 <= nc < M:
                            nchar = grid[nr][nc]
                            if nchar == '.' or (nchar == 'R' and m == 1) or (nchar == 'B' and m == 0):
                                adj[u].append(get_state(nr, nc, m))
                           
        queries = []
        for i in range(Q):
            r1 = int(next(interationthignie))
            c1 = int(next(interationthignie))
            r2 = int(next(interationthignie))
            c2 = int(next(interationthignie))
            K = int(next(interationthignie))
            queries.append((r1, c1, r2, c2, K, i))
            
        ans_dist = [10**15] * Q
        dist_array = [-1] * S
        
        def dandq(L, R, curr_queries):
            if L > R or not curr_queries:
                return
            
            mid = (L + R) // 2
            
            ext_L = max(0, L - 25)
            ext_R = min(M - 1, R + 25)
            
            mid_dists = []
            
            for r_mid in range(N):
                for m_mid in (0, 1):
                    start_state = get_state(r_mid, mid, m_mid)
                    
                    q = deque([start_state])
                    dist_array[start_state] = 0
                    visited_nodes = [start_state]
                    
                    while q:
                        u = q.popleft()
                        d = dist_array[u]
                        for v in adj[u]:
                            v_c = (v // 2) % M
                            if ext_L <= v_c <= ext_R:
                                if dist_array[v] == -1:
                                    dist_array[v] = d + 1
                                    q.append(v)
                                    visited_nodes.append(v)
                                    
                    local_dist = {node: dist_array[node] for node in visited_nodes}
                    mid_dists.append(local_dist)
                    
                    for node in visited_nodes:
                        dist_array[node] = -1
            
            next_left = []
            next_right = []
            
            for q_tuple in curr_queries:
                r1, c1, r2, c2, K, idx = q_tuple
                
                if min(c1, c2) <= mid <= max(c1, c2):
                    s_state = get_state(r1, c1, 0) 
                    t_state_0 = get_state(r2, c2, 0)
                    t_state_1 = get_state(r2, c2, 1)
                    
                    min_d = 10**15
                    for local_dist in mid_dists:
                        if s_state in local_dist:
                            d1 = local_dist[s_state]
                            d2_0 = local_dist.get(t_state_0, 10**15)
                            d2_1 = local_dist.get(t_state_1, 10**15)
                            
                            if d1 + d2_0 < min_d: min_d = d1 + d2_0
                            if d1 + d2_1 < min_d: min_d = d1 + d2_1
                            
                    ans_dist[idx] = min_d
                elif max(c1, c2) < mid:
                    next_left.append(q_tuple)
                else:
                    next_right.append(q_tuple)
            
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