import sys
import collections

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
        
        grid_mask = [[0] * M for _ in range(N)]
        for r in range(N):
            row = grid[r]
            for c in range(M):
                char = row[c]
                if char == '.':
                    grid_mask[r][c] = 3
                elif char == 'R':
                    grid_mask[r][c] = 2
                elif char == 'B':
                    grid_mask[r][c] = 1
                    
        queries = []
        for i in range(Q):
            r1 = int(next(iterator))
            c1 = int(next(iterator))
            r2 = int(next(iterator))
            c2 = int(next(iterator))
            K = int(next(iterator))
            queries.append((r1, c1, r2, c2, K, i))
            
        ans_dist = [10**15] * Q
        dist_array = [-1] * (N * M * 2)
        
        def dandq(L, R, curr_queries):
            if L > R or not curr_queries:
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
                by_source = collections.defaultdict(list)
                for q_tuple in mid_queries:
                    r1, c1, r2, c2, K, idx = q_tuple
                    by_source[(r1, c1)].append((r2, c2, idx))
                
                for (s_r, s_c), targets in by_source.items():
                    start_state = (s_r * M + s_c) * 2
                    q = collections.deque([start_state])
                    dist_array[start_state] = 0
                    visited_nodes = [start_state]
                    
                    while q:
                        u = q.popleft()
                        d = dist_array[u]
                        
                        curr_m = u % 2
                        rem = u // 2
                        curr_c = rem % M
                        curr_r = rem // M
                        
                        if grid_mask[curr_r][curr_c] == 3:
                            nxt = u ^ 1
                            if dist_array[nxt] == -1:
                                dist_array[nxt] = d + 1
                                q.append(nxt)
                                visited_nodes.append(nxt)
                                
                        for dr, dc in ((-1, 0), (1, 0), (0, -1), (0, 1)):
                            nr, nc = curr_r + dr, curr_c + dc
                            if 0 <= nr < N and 0 <= nc < M:
                                mask = grid_mask[nr][nc]
                                if (curr_m == 0 and (mask & 1)) or (curr_m == 1 and (mask & 2)):
                                    nxt = (nr * M + nc) * 2 + curr_m
                                    if dist_array[nxt] == -1:
                                        dist_array[nxt] = d + 1
                                        q.append(nxt)
                                        visited_nodes.append(nxt)
                                        
                    for t_r, t_c, idx in targets:
                        t_0 = (t_r * M + t_c) * 2
                        t_1 = t_0 + 1
                        min_d = 10**15
                        if dist_array[t_0] != -1: min_d = min(min_d, dist_array[t_0])
                        if dist_array[t_1] != -1: min_d = min(min_d, dist_array[t_1])
                        ans_dist[idx] = min_d
                        
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
