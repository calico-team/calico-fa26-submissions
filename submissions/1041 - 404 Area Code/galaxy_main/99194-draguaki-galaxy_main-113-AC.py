import sys


sys.setrecursionlimit(200000)

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
        
    iterator = iter(input_data)
    num_test_cases = int(next(iterator))
    
    for _ in range(num_test_cases):
        N = int(next(iterator))
        M = int(next(iterator))
        Q = int(next(iterator))
        
        grid = []
        for _ in range(N):
            grid.append(next(iterator))
        num_nodes = 2 * N * M
        comp_id = [-1] * num_nodes
        current_id = 0
        

        for start_node in range(num_nodes):
            if comp_id[start_node] != -1:
                continue
                

            queue = [start_node]
            comp_id[start_node] = current_id
            head = 0
            
            while head < len(queue):
                curr = queue[head]
                head += 1
                

                state = curr // (N * M)
                rem = curr % (N * M)
                r = rem // M
                c = rem % M
                
              
                for dr, dc in [(-1,0), (1,0), (0,-1), (0,1)]:
                    nr, nc = r + dr, c + dc
                    if 0 <= nr < N and 0 <= nc < M:
                       
                        tile = grid[nr][nc]
                        can_walk = False
                        if tile == '.':
                            can_walk = True
                        elif state == 0 and tile == 'B':
                            can_walk = True
                        elif state == 1 and tile == 'R':
                            can_walk = True
                            
                        if can_walk:
                            nxt_node = state * (N * M) + nr * M + nc
                            if comp_id[nxt_node] == -1:
                                comp_id[nxt_node] = current_id
                                queue.append(nxt_node)
                                
            
                if grid[r][c] == '.':
                    nxt_state = 1 - state
                    nxt_node = nxt_state * (N * M) + r * M + c
                    if comp_id[nxt_node] == -1:
                        comp_id[nxt_node] = current_id
                        queue.append(nxt_node)
                        
            current_id += 1
        for _ in range(Q):
            r_start = int(next(iterator))
            c_start = int(next(iterator))
            r_end = int(next(iterator))
            c_end = int(next(iterator))
            

            start_node = 0 * (N * M) + r_start * M + c_start
            start_component = comp_id[start_node]
            
    
            end_node_blue = 0 * (N * M) + r_end * M + c_end
            end_node_red = 1 * (N * M) + r_end * M + c_end
            
            if comp_id[end_node_blue] == start_component or comp_id[end_node_red] == start_component:
                print("YES")
            else:
                print("NO")

if __name__ == "__main__":
    solve()
