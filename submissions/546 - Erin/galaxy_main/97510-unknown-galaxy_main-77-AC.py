import sys
sys.setrecursionlimit(50000)
for _ in range(int(input())):
    n,m,q=map(int,input().split())
    g=[]
    for _ in range(n):
        g.append([x for x in input()])
    vis = [[False for _ in range(m)] for _ in range(n)]
    def search(r, c):
        if not vis[r][c]:
            vis[r][c] = True
            if g[r][c] == '.':
                if r > 0 and not vis[r - 1][c]:
                    search(r - 1, c)
                if r < n - 1 and not vis[r + 1][c]:
                    search(r + 1, c)
                if c > 0 and not vis[r][c - 1]:
                    search(r, c - 1)
                if c < m - 1 and not vis[r][c + 1]:
                    search(r, c + 1)
            elif g[r][c] == 'B':
                if r > 0 and g[r - 1][c] != 'R' and not vis[r - 1][c]:
                    search(r - 1, c)
                if r < n - 1 and g[r + 1][c] != 'R' and not vis[r + 1][c]:
                    search(r + 1, c)
                if c > 0 and g[r][c - 1] != 'R' and not vis[r][c - 1]:
                    search(r, c - 1)
                if c < m - 1 and g[r][c + 1] != 'R' and not vis[r][c + 1]:
                    search(r, c + 1)
            else:
                if r > 0 and g[r - 1][c] != 'B' and not vis[r - 1][c]:
                    search(r - 1, c)
                if r < n - 1 and g[r + 1][c] != 'B' and not vis[r + 1][c]:
                    search(r + 1, c)
                if c > 0 and g[r][c - 1] != 'B' and not vis[r][c - 1]:
                    search(r, c - 1)
                if c < m - 1 and g[r][c + 1] != 'B' and not vis[r][c + 1]:
                    search(r, c + 1)
    search(n-1, m-1)
    for _ in range(q):
        rs,cs,re,ce=map(int,input().split())
        if vis[rs][cs]:
            print('YES')
        else:
            print('NO')
