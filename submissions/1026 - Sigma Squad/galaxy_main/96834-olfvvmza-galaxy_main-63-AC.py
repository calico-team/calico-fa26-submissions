import sys
from collections import deque

input = sys.stdin.readline

t = int(input())
res = []
for _ in range(t):
    n, m, q = map(int, input().split())
    g = [input().strip() for _ in range(n)]

    def good(r, c, k):
        if g[r][c] == '.':
            return True
        if k == 0:
            return g[r][c] == 'B'
        return g[r][c] == 'R'

    comp = [[[-1, -1] for _ in range(m)] for _ in range(n)]
    cnt = 0
    for i in range(n):
        for j in range(m):
            for k in range(2):
                if comp[i][j][k] != -1 or not good(i, j, k):
                    continue
                comp[i][j][k] = cnt
                dq = deque([(i, j, k)])
                while dq:
                    x, y, z = dq.popleft()
                    if g[x][y] == '.' and comp[x][y][1-z] == -1:
                        comp[x][y][1-z] = cnt
                        dq.append((x, y, 1-z))
                    for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                        a, b = x + dx, y + dy
                        if 0 <= a < n and 0 <= b < m and comp[a][b][z] == -1 and good(a, b, z):
                            comp[a][b][z] = cnt
                            dq.append((a, b, z))
                cnt += 1

    for _ in range(q):
        r1, c1, r2, c2 = map(int, input().split())
        s = comp[r1][c1][0]
        if s != -1 and s in comp[r2][c2]:
            res.append("YES")
        else:
            res.append("NO")

print("\n".join(res))
