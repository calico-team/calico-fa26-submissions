import sys
from collections import deque
from functools import lru_cache

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    idx = 0
    t = int(input_data[idx])
    idx += 1
    
    out = []
    
    for _ in range(t):
        n = int(input_data[idx])
        m = int(input_data[idx+1])
        q = int(input_data[idx+2])
        idx += 3
        
        grid = []
        for _ in range(n):
            grid.append(input_data[idx])
            idx += 1
            
        queries = []
        for _ in range(q):
            r1 = int(input_data[idx])
            c1 = int(input_data[idx+1])
            r2 = int(input_data[idx+2])
            c2 = int(input_data[idx+3])
            k = int(input_data[idx+4])
            idx += 5
            queries.append((r1, c1, r2, c2, k))
            
        dirs = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        
       
        @lru_cache(maxsize=256)
        def get_dist_grid(r_start, c_start):
            dist = [[[float('inf'), float('inf')] for _ in range(m)] for _ in range(n)]
            queue = deque([(r_start, c_start, 0)])
            dist[r_start][c_start][0] = 0
            
            while queue:
                r, c, mode = queue.popleft()
                d = dist[r][c][mode]
                
               
                if grid[r][c] == '.':
                    nm = 1 - mode
                    if d + 1 < dist[r][c][nm]:
                        dist[r][c][nm] = d + 1
                        queue.append((r, c, nm))
                        
             
                for dr, dc in dirs:
                    nr, nc = r + dr, c + dc
                    if 0 <= nr < n and 0 <= nc < m:
                        ntile = grid[nr][nc]
                        valid = (ntile == '.' or (mode == 0 and ntile == 'B') or (mode == 1 and ntile == 'R'))
                        if valid and d + 1 < dist[nr][nc][mode]:
                            dist[nr][nc][mode] = d + 1
                            queue.append((nr, nc, mode))
                            
            return dist
        
        for r1, c1, r2, c2, k in queries:
            if not (0 <= r1 < n and 0 <= c1 < m and 0 <= r2 < n and 0 <= c2 < m):
                out.append("NO")
                continue
                
            dist = get_dist_grid(r1, c1)
            min_time = min(dist[r2][c2][0], dist[r2][c2][1])
            
            if min_time <= k:
                out.append("YES")
            else:
                out.append("NO")
                
    print('\n'.join(out))

if __name__ == '__main__':
    solve()