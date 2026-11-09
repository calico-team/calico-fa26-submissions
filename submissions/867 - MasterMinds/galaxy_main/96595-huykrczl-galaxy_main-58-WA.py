import sys
from collections import deque

def solve():
    data = sys.stdin.read().split()
    if not data:
        return
    
    it = iter(data)
    t = int(next(it))
    out = []
    
    for i in range(t):
        n = int(next(it))
        m = int(next(it))
        q = int(next(it))
        
        grid = [next(it) for i in range(n)]
        
        queries = []
        for i in range(q):
            r1 = int(next(it))
            c1 = int(next(it))
            r2 = int(next(it))
            c2 = int(next(it))
            queries.append((r1, c1, r2, c2))
            
       
        visited = [[[False, False] for _ in range(m)] for _ in range(n)]
        queue = deque([(0, 0, 0)])
        visited[0][0][0] = True
        
        while queue:
            r, c, mode = queue.popleft()
            
            
            if grid[r][c] == '.' and not visited[r][c][1 - mode]:
                visited[r][c][1 - mode] = True
                queue.append((r, c, 1 - mode))
                
           
            for dr, dc in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                nr, nc = r + dr, c + dc
                if 0 <= nr < n and 0 <= nc < m:
                    tile = grid[nr][nc]
                   
                    if tile == '.' or (mode == 0 and tile == 'B') or (mode == 1 and tile == 'R'):
                        if not visited[nr][nc][mode]:
                            visited[nr][nc][mode] = True
                            queue.append((nr, nc, mode))
                            
       
        for r1, c1, r2, c2 in queries:
            if visited[r1][c1][0]:
                out.append("YES")
            else:
                out.append("NO")
                
    print('\n'.join(out))

if __name__ == '__main__':
    solve()