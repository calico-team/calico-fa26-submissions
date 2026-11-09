t = int(input())
for _ in range(t):
    n, m, q = map(int, input().split())
    grid = []
    for _ in range(n):
        grid.append(list(input().strip()))
    
    grid2 = [[0 for _ in range(m)] for _ in range(n)]

    visited = [[False for _ in range(m)] for _ in range(n)]

    num = 1

    for i in range(n):
        for j in range(m):
            if visited[i][j]:
                continue 
            
            lst = [(i, j)]

            while lst:
                i1, j1 = lst.pop()

                grid2[i1][j1] = num
                visited[i1][j1] = True 

                color = grid[i1][j1]
                if color == '.':
                    can_visit = ['.', 'R', 'B']
                elif color == 'R':
                    can_visit = ['R', '.']
                elif color == 'B':
                    can_visit = ['B', '.']

                if i1 > 0:
                    if not visited[i1 - 1][j1] and grid[i1 - 1][j1] in can_visit:
                        lst.append((i1 - 1, j1))
                        visited[i1 - 1][j1] = True
                
                if j1 > 0:
                    if not visited[i1][j1 - 1] and grid[i1][j1 - 1] in can_visit:
                        lst.append((i1, j1 - 1))
                        visited[i1][j1 - 1] = True
                
                if i1 < n - 1:
                    if not visited[i1 + 1][j1] and grid[i1 + 1][j1] in can_visit:
                        lst.append((i1 + 1, j1))
                        visited[i1 + 1][j1] = True
                
                if j1 < m - 1:
                    if not visited[i1][j1 + 1] and grid[i1][j1 + 1] in can_visit:
                        lst.append((i1, j1 + 1))
                        visited[i1][j1 + 1] = True
                
            num += 1
    
    #for lst in grid2:
    #    print(lst)
    
    for _ in range(q):
        r1, c1, r2, c2 = map(int, input().split())
        if grid2[r1][c1] == grid2[r2][c2]:
            print('YES')
        else:
            print('NO')

