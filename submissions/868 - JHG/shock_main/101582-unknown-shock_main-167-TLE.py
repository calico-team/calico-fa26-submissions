t = int(input())

for i in range(t):
    n, m, q = map(int,input().split())
    grid = [[0]*m for i in range(n)]
    for i in range(q):
        r,c,p = map(int,input().split())
        for row in range(n):
            for col in range(m):
                result = p**2 - (((row-r)**2) + ((col-c)**2))+1
                if result>0:
                    grid[row][col] = result
    for i in range(n):
        print(*grid[i])
