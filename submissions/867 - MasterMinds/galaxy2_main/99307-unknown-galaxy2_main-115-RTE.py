import sys
from collections import deque

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    it = iter(input_data)
    t = int(next(it))
    out = []
    
    for _ in range(t):
        n = int(next(it))
        m = int(next(it))
        q = int(next(it))
        
        grid = [next(it) for _ in range(n)]
        
        queries = []
        for _ in range(q):
            r1 = int(next(it))
            c1 = int(next(it))
            r2 = int(next(it))
            c2 = int(next(it))
            k = int(next(it))
            queries.append((r1, c1, r2, c2, k))
            
        
        dist_cache = {}
        dirs = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        
        for r1, c1, r2, c2, k in queries:  #
            if not (0 <= r1 < n and 0 <= c1 < m and 0 <= r2 < n and 0 <= c2 < m):
                out.append("NO")
                continue
                
            start_key = (r1, c1)
            
            if start_key not in dist_cache:
              
                dist = [[[float('inf'), float('inf')] for _ in range(m)] for _ in range(n)]
                queue = deque([(r1, c1, 0)])
                dist[r1][c1][0] = 0
                
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
                                
                dist_cache[start_key] = dist
            
            dist = dist_cache[start_key]
            min_time = min(dist[r2][c2][0], dist[r2][c2][1])
            
            if min_time <= k:
                out.append("YES")
            else:
                out.append("NO")
                
    print('\n'.join(out))

if __name__ == '__main__':
    solve()