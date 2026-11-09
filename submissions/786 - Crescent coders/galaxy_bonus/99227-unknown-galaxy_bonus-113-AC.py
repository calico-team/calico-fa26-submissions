
from collections import deque

def solve():
    T = int(input())

    for _ in range(T):
        n, m, q = map(int, input().split())
        grid = [input().strip() for _ in range(n)]

        
        comp = [[[-1] * m for _ in range(n)]
                for _ in range(2)]

        directions = [(1, 0), (-1, 0),
                      (0, 1), (0, -1)]

        group = 0

        
        for mode in range(2):
            for r in range(n):
                for c in range(m):

                    tile = grid[r][c]

                    if comp[mode][r][c] != -1:
                        continue

                    if mode == 0 and tile == 'R':
                        continue
                    if mode == 1 and tile == 'B':
                        continue

                    queue = deque([(r, c, mode)])
                    comp[mode][r][c] = group

                    while queue:
                        x, y, current = queue.popleft()

                       
                        if grid[x][y] == '.':
                            other = 1 - current

                            if comp[other][x][y] == -1:
                                comp[other][x][y] = group
                                queue.append((x, y, other))

                       
                        for dx, dy in directions:
                            nx, ny = x + dx, y + dy

                            if not (0 <= nx < n and
                                    0 <= ny < m):
                                continue

                            if comp[current][nx][ny] != -1:
                                continue

                            next_tile = grid[nx][ny]

                            if current == 0 and next_tile == 'R':
                                continue
                            if current == 1 and next_tile == 'B':
                                continue

                            comp[current][nx][ny] = group
                            queue.append((nx, ny, current))

                    group += 1

      
        for _ in range(q):
            sr, sc, er, ec = map(int, input().split())

            start = comp[0][sr][sc]
            end_tile = grid[er][ec]

            if end_tile == 'R':
                end = comp[1][er][ec]
            else:
                end = comp[0][er][ec]

            print("YES" if start == end else "NO")


solve()
