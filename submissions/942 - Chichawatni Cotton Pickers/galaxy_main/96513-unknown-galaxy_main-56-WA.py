import sys
from collections import deque

def solve(N: int, M: int, Q: int, grid: list, queries: list) -> list:
    """
    For each query, determine whether Ben can successfully get from his starting 
    location (R_start, C_start) to the bottom right corner (N-1, M-1).
    """
    
    num_states = N * M * 2
    visited = [False] * num_states
    
    target_state = (N - 1) * M * 2 + (M - 1) * 2 + 0
    
    queue = deque([target_state])
    visited[target_state] = True
    
    queue = deque()

    target_blue = (N - 1) * M * 2 + (M - 1) * 2 + 0
    target_red = (N - 1) * M * 2 + (M - 1) * 2 + 1
    
    queue.append(target_blue)
    visited[target_blue] = True
    if grid[N-1][M-1] == '.':
        queue.append(target_red)
        visited[target_red] = True
        
    dr = [-1, 1, 0, 0]
    dc = [0, 0, -1, 1]
    
    while queue:
        curr = queue.popleft()
        r = curr // (M * 2)
        rem = curr % (M * 2)
        c = rem // 2
        mode = rem % 2
        
        for i in range(4):
            nr, nc = r + dr[i], c + dc[i]
            if 0 <= nr < N and 0 <= nc < M:
                tile = grid[nr][nc]
                is_active = (tile == '.') or (tile == 'B' and mode == 0) or (tile == 'R' and mode == 1)
                if is_active:
                    n_state = nr * M * 2 + nc * 2 + mode
                    if not visited[n_state]:
                        visited[n_state] = True
                        queue.append(n_state)
                        
        if grid[r][c] == '.':
            n_mode = 1 - mode
            n_state = r * M * 2 + c * 2 + n_mode
            if not visited[n_state]:
                visited[n_state] = True
                queue.append(n_state)
                
    results = []
    for r_start, c_start, r_end, c_end in queries:
        start_state = r_start * M * 2 + c_start * 2 + 0 # starts in Blue mode
        if visited[start_state]:
            results.append("YES")
        else:
            results.append("NO")
            
    return results

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    T = int(input_data[0])
    idx = 1
    for _ in range(T):
        N = int(input_data[idx])
        M = int(input_data[idx+1])
        Q = int(input_data[idx+2])
        idx += 3
        
        grid = []
        for _ in range(N):
            grid.append(input_data[idx])
            idx += 1
            
        queries = []
        for _ in range(Q):
            r_start = int(input_data[idx])
            c_start = int(input_data[idx+1])
            r_end = int(input_data[idx+2])
            c_end = int(input_data[idx+3])
            idx += 4
            queries.append((r_start, c_start, r_end, c_end))
            
        outputs = solve(N, M, Q, grid, queries)
        for out in outputs:
            print(out)

if __name__ == '__main__':
    main()
