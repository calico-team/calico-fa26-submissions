import sys
from collections import deque

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    idx = 0
    num_test_cases = int(input_data[idx])
    idx += 1
    
    out = []
    for _ in range(num_test_cases):
        N = int(input_data[idx])
        M = int(input_data[idx+1])
        Q = int(input_data[idx+2])
        idx += 3
        
        grid = []
        for _ in range(N):
            grid.append(input_data[idx])
            idx += 1
            
        for _ in range(Q):
            r_start = int(input_data[idx])
            c_start = int(input_data[idx+1])
            r_end = int(input_data[idx+2])
            c_end = int(input_data[idx+3])
            K = int(input_data[idx+4])
            idx += 5
            
            # Quick check: Manhattan distance is a lower bound
            manhattan = abs(r_start - r_end) + abs(c_start - c_end)
            if manhattan > K:
                out.append("NO")
                continue
            
            # BFS state: (r, c, mode)
            # mode: 0 for blue mode, 1 for red mode
            # Start in blue mode (0) at (r_start, c_start)
            queue = deque([(r_start, c_start, 0, 0)]) # (r, c, mode, dist)
            visited = {}
            visited[(r_start, c_start, 0)] = 0
            
            possible = False
            
            while queue:
                r, c, mode, dist = queue.popleft()
                
                if r == r_end and c == c_end:
                    if dist <= K:
                        possible = True
                        break
                
                if dist >= K:
                    continue
                
                # 1. Try moving to adjacent cells
                for dr, dc in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                    nr, nc = r + dr, c + dc
                    if 0 <= nr < N and 0 <= nc < M:
                        cell = grid[nr][nc]
                        # Check if tile is active
                        is_active = (cell == '.') or (cell == 'B' and mode == 0) or (cell == 'R' and mode == 1)
                        if is_active:
                            next_state = (nr, nc, mode)
                            next_dist = dist + 1
                            if next_state not in visited or visited[next_state] > next_dist:
                                visited[next_state] = next_dist
                                queue.append((nr, nc, mode, next_dist))
                                
                # 2. If current tile is normal ('.'), try spin action
                if grid[r][c] == '.':
                    next_mode = 1 - mode
                    next_state = (r, c, next_mode)
                    next_dist = dist + 1
                    if next_state not in visited or visited[next_state] > next_dist:
                        visited[next_state] = next_dist
                        queue.append((r, c, next_mode, next_dist))
                        
            out.append("YES" if possible else "NO")
            
    print('\n'.join(out))

if __name__ == '__main__':
    solve()
