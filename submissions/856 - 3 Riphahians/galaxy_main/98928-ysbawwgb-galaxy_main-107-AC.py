import sys

def solve():
    input=sys.stdin.readline
    quantity=int(input())
    for i in range(quantity):
        n,m,q=map(int,input().split())
        g=[input().strip() for i in range(n)]
        a=[[0]*m for i in range(n)]
        count=0
        for i in range(n):
            for j in range(m):
                if a[i][j]!=0:
                    continue
                count+=1
                a[i][j]=count
                stack=[(i,j)]
                while stack:
                    x,y=stack.pop()
                    for nx,ny in((x-1,y),(x+1,y),(x,y-1),(x,y+1)):
                        if 0<=nx<n and 0<=ny<m and a[nx][ny]==0:
                            if g[x][y]=="." or g[nx][ny]=="." or g[x][y]==g[nx][ny]:
                                a[nx][ny]=count
                                stack.append((nx,ny))
        for i in range(q):
            r1,c1,r2,c2=map(int,input().split())
            if a[r1][c1]==a[r2][c2]:
                print("YES")
            else:
                print("NO")

solve()
