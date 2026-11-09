from collections import deque
m = int(input())
for i in range(m):
    r,c,s = map(int,input().split())
    array = []
    for i in range(r):
        array.append(list(input().strip()))
    def find(cr,cc):
        q = deque()
        vis = [[[False] * 2 for _ in range(c)] for _ in range(r)]
        if array[cr][cc] == 'B':
            q.append((cr,cc,0))
            vis[cr][cc][0] = True
        elif array[cr][cc] == 'R':
            q.append((cr,cc,1))
            vis[cr][cc][1] = True
        else:
            q.append((cr,cc,1))
            q.append((cr,cc,1))
            vis[cr][cc][0] = True
            vis[cr][cc][1] = True
        dr = [-1,1,0,0]
        dc = [0,0,-1,1]
        while q:
            global found

            cr,cc,status = q.popleft()
            if cr == er and cc == ec:
                print('YES')
                found = True
                break
            for i in range(4):
                nr = dr[i] + cr
                nc = dc[i] + cc
                if 1 == 1:
                    if status == 0:
                        if 0 <=nr < r and 0 <=nc < c:
                            if 1 == 1:
                                if array[nr][nc] == 'B':
                                    if not vis[nr][nc][0]:
                                        vis[nr][nc][0] = True
                                        q.append((nr,nc,0))
                                elif array[nr][nc] == 'R'and array[cr][cc] == '.':
                                    if not vis[nr][nc][1]:
                                        vis[nr][nc][1] = True
                                        q.append((nr,nc,1))
                                elif array[nr][nc] == '.':
                                    if not vis[nr][nc][0]:
                                        vis[nr][nc][0] = True
                                        q.append((nr,nc,0))
                    if status == 1:
                        if 0 <= nr < r and 0 <=nc < c:
                            if 1 == 1:
                                if array[nr][nc] == 'R':
                                    if not vis[nr][nc][1]:
                                        vis[nr][nc][1] = True
                                        q.append((nr,nc,1))
                                elif array[nr][nc] == 'B' and array[cr][cc] == '.':
                                    if not vis[nr][nc][0]:
                                        vis[nr][nc][0] = True
                                        q.append((nr,nc,0))
                                elif array[nr][nc] == '.':
                                    if not vis[nr][nc][1]:
                                        vis[nr][nc][1] = True
                                        q.append((nr,nc,1))
                
                
    for i in range(s):
        cr,cc,er,ec = map(int,input().split())
        found = False
        find(cr,cc)
        if not found:
            print('NO')

            
        
        
    
