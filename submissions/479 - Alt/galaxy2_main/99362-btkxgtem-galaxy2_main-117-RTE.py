import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    iterator = iter(input_data)
    num_test_cases = int(next(iterator))
    
    output = []
    INF = 10**15
    
    for _ in range(num_test_cases):
        N = int(next(iterator))
        M = int(next(iterator))
        Q = int(next(iterator))
        
        flat_grid = "".join(next(iterator) for _ in range(N))
        
        S = N * M * 2
        
        dist_cache = {}
        
        valid_moves = []
        for i in range(N * M):
            r = i // M
            c = i % M
            moves = []
            if r > 0:     moves.append(-M)  
            if r < N - 1: moves.append(M)   
            if c > 0:     moves.append(-1)  
            if c < M - 1: moves.append(1)   
            valid_moves.append(moves)

        for _ in range(Q):
            r_start = int(next(iterator))
            c_start = int(next(iterator))
            r_end = int(next(iterator))
            c_end = int(next(iterator))
            K = int(next(iterator))
            
            start_cell = r_start * M + c_start
            
            if start_cell not in dist_cache:
                d = [INF] * S
                start_state = start_cell * 2 + 0 
                d[start_state] = 0
                
                q = [start_state]
                head = 0
                
                while head < len(q):
                    u = q[head]
                    head += 1
                    curr_d = d[u]
                    
                    cell_idx = u // 2
                    m = u % 2
                    
                    if flat_grid[cell_idx] == '.':
                        if curr_d + 1 < d[v]:
                            d[v] = curr_d + 1
                            q.append(v)
                            
                    for offset in valid_moves[cell_idx]:
                        n_cell = cell_idx + offset
                        cell_type = flat_grid[n_cell]
                        
                        if cell_type == '.' or (cell_type == 'R' and m == 1) or (cell_type == 'B' and m == 0):
                            v = n_cell * 2 + m
                            if curr_d + 1 < d[v]:
                                d[v] = curr_d + 1
                                q.append(v)
                                
                dist_cache[start_cell] = d
                
            d_arr = dist_cache[start_cell]
            end_cell = r_end * M + c_end
            
            ans = min(d_arr[end_cell * 2], d_arr[end_cell * 2 + 1])
            
            if ans <= K:
                output.append("YES")
            else:
                output.append("NO")
                
    sys.stdout.write('\n'.join(output) + '\n')

if __name__ == '__main__':
    solve()
