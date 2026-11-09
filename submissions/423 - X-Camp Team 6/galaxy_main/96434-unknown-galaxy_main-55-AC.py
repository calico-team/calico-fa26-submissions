from collections import deque

for thing in range(int(input())):
    n, m, q = map(int, input().split())
    g=[input().strip() for _ in range(n)]
    list3D =[[[-1, -1] for _ in range(m)] for _ in range(n)]
    num = 0
    for i in range(n):
        for j in range(m):
            for s in range(2):
                if list3D[i][j][s] != -1:continue
                if g[i][j] == "R" and s == 0:continue
                if g[i][j] == "B" and s == 1:continue
                list3D[i][j][s] = num
                todo =deque([(i, j, s)])
                while todo:
                    r, c, st=todo.popleft()
                    for dr, dc in ((-1, 0),(1, 0),(0, -1),(0, 1)):
                        nr, nc = r+dr,c + dc
                        if 0<= nr< n and 0 <=nc <m:
                            ch = g[nr][nc]
                            if ch == "R" and st == 0: continue
                            if ch =="B" and st==1: continue
                            if list3D[nr][nc][st] == -1:
                                list3D[nr][nc][st] = num
                                todo.append((nr, nc, st))
                    if g[r][c] ==".":
                        nxt = 1-st
                        if list3D[r][c][nxt]==-1:
                            list3D[r][c][nxt] =num
                            todo.append((r, c, nxt))
                num += 1
    for thing2 in range(q):
        r1, c1, r2, c2 = map(int, input().split())
        ans = False
        for s in range(2):
            for t in range(2):
                if list3D[r1][c1][s] == list3D[r2][c2][t] and list3D[r1][c1][s] != -1:
                    ans = True
        if ans == True:
            print("YES")
        if ans == False:
            print("NO")
