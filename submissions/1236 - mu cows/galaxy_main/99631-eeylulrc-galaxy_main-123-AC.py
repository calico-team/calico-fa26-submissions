import sys
from collections import deque # for bfs and le'ts just use python cause java kinda bad for htis

def walkable(tile, active):
    return tile == '.' or (tile == 'R' and active == 0) or (tile == 'B' and active == 1)

token = iter(sys.stdin.read().split())
out = []
t = int(next(token))
for i in range(t):
    n = int(next(token))
    m = int(next(token))
    q = int(next(token))
    grid = [next(token) for j in range(n)]

    queue = deque()
    tried = set()
    for active in (0,1):
        if walkable(grid[n-1][m-1], active):
            tried.add((n-1, m-1, active))
            queue.append((n-1, m-1, active))

    while queue:
        r, c, active = queue.popleft()
        if grid[r][c] == '.' and (r,c,1-active) not in tried:
            tried.add((r,c, 1-active))
            queue.append((r, c, 1-active))
        
        for newr, newc in ((r-1,c), (r+1, c), (r, c-1), (r, c+1)):
            if 0 <= newr < n and 0 <= newc < m and (newr, newc, active) not in tried:
                if walkable(grid[newr][newc], active):
                    tried.add((newr, newc, active))
                    queue.append((newr, newc, active))

    for d in range(q):
        startr = int(next(token))
        startc = int(next(token))
        next(token)
        next(token) # lowkey doesn't work without this i think it's just abuffer thing 
        out.append("YES" if (startr, startc, 1) in tried else "NO")

print("\n".join(out))

