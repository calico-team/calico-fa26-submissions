t = int(input())
for _ in range(t):
    n,m,q = map(int,input().split())
    grid = []
    for i in range(n):
        grid.append(input())
    def grid_index(x,y):
        return x*m+y
    dj_p = list(range(n*m))
    def dj_parent(i:int):
        if dj_p[i]==i:
            return i
        parent = dj_parent(dj_p[i])
        dj_p[i]=parent
        return parent
    def dj_union(i:int,j:int):
        dj_p[dj_parent(i)]=dj_parent(j)
    def union_grid(x1,y1,x2,y2):
        if 0<=x2 and x2<n and 0<=y2 and y2<m:
            if grid[x1][y1]=="R" and grid[x2][y2]=="B":
                return
            if grid[x1][y1]=="B" and grid[x2][y2]=="R":
                return
            dj_union(grid_index(x1,y1),grid_index(x2,y2))
    for x in range(n):
        for y in range(m):
            union_grid(x,y,x+1,y)
            union_grid(x,y,x-1,y)
            union_grid(x,y,x,y+1)
            union_grid(x,y,x,y-1)
    for i in range(q):
        x1,y1,x2,y2 = map(int,input().split())
        print(("NO","YES")[dj_parent(grid_index(x1,y1))==dj_parent(grid_index(x2,y2))])