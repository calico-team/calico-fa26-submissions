from collections import deque
for _ in range(int(input())):
    rows,columns,earthquakes=map(int,input().split())
    def check(nr, nc):
        if 0<=nr<rows and 0<=nc<columns:
            return True
        return False
    grid=[[0]*columns for _ in range(rows)]
    for _ in range(earthquakes):
        row,column,power=map(int,input().split())
        grid[row][column]=power*power+1
        queue=deque([(row,column)])
        visited={(row,column)}
        while queue:
            rowr,columnn=queue.popleft()
            for dr,dc in ((-1,0),(1,0),(0,-1),(0,1)):
                nr=rowr+dr
                nc=columnn+dc
                if check(nr,nc) and (nr,nc) not in visited:
                    val=max(power*power+1-abs(nr-row)**2-abs(nc-column)**2,0)
                    if val>0:
                        grid[nr][nc]=val
                        queue.append((nr,nc))
                    visited.add((nr,nc))
    for i in grid:
        print(*i)