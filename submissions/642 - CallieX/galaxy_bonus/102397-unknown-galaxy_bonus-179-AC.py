
t = int(input())

for _ in range(t):
    n, m, q = map(int, input().split())

    grid = [input() for i in range(n)]

    visited = [[[-1, -1] for j in range(m)] for i in range(n)]

    directions = [(0,1), (0,-1), (1,0), (-1,0)]

    from collections import deque

    group = 0

    for i in range(n):
        for j in range(m):
            for mode in range(2):

                color = 'B' if mode == 0 else 'R'

                if grid[i][j] != '.' and grid[i][j] != color:
                    continue

                if visited[i][j][mode] != -1:
                    continue

                q1 = deque([(i, j, mode)])
                visited[i][j][mode] = group

                while q1:
                    x, y, mode = q1.popleft()

                    if grid[x][y] == '.':
                        new_mode = 1 - mode

                        if visited[x][y][new_mode] == -1:
                            visited[x][y][new_mode] = group
                            q1.append((x, y, new_mode))

                    for dx, dy in directions:
                        a = x + dx
                        b = y + dy

                        if 0 <= a < n and 0 <= b < m:
                            color = 'B' if mode == 0 else 'R'

                            if grid[a][b] == '.' or grid[a][b] == color:
                                if visited[a][b][mode] == -1:
                                    visited[a][b][mode] = group
                                    q1.append((a, b, mode))

                group += 1

    for _ in range(q):
        sr, sc, er, ec = map(int, input().split())

        if grid[er][ec] == '.':
            if visited[sr][sc][0] == visited[er][ec][0]:
                print("YES")
            else:
                print("NO")

        else:
            mode = 0 if grid[er][ec] == 'B' else 1

            if visited[sr][sc][0] == visited[er][ec][mode]:
                print("YES")
            else:
                print("NO")
