import sys
from collections import deque

for _ in range(int(input())):
    n, m, Q = map(int, input().split())
    grid = [input().strip() for _ in range(n)]
    
    def active(r, c, mode):
        t = grid[r][c]
        return t == '.' or (t == 'B' and mode == 0) or (t == 'R' and mode == 1)
    
    comp = [[[-1] * m for _ in range(n)] for _ in range(2)]
    group = 0
    
    for mode in range(2):
        for r in range(n):
            for c in range(m):
                if comp[mode][r][c] != -1 or not active(r, c, mode):
                    continue
                comp[mode][r][c] = group
                q = deque([(mode, r, c)])
                while q:
                    md, x, y = q.popleft()
                    nexts = []
                    for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                        nx, ny = x + dx, y + dy
                        if 0 <= nx < n and 0 <= ny < m and active(nx, ny, md):
                            nexts.append((md, nx, ny))
                    if grid[x][y] == '.':
                        nexts.append((1 - md, x, y))
                    for s in nexts:
                        if comp[s[0]][s[1]][s[2]] == -1:
                            comp[s[0]][s[1]][s[2]] = group
                            q.append(s)
                group += 1
    
    for _ in range(Q):
        rs, cs, re, ce = map(int, input().split())
        start = comp[0][rs][cs]
        if start == comp[0][re][ce] or start == comp[1][re][ce]:
            print("YES")
        else:
            print("NO")