from collections import deque
t = int(input())
for _ in range(t):
    n, m, q = map(int, input().split())
    grid = [list(input().split()) for i in range(n)]
    query = [list(map(int, input().split())) for i in range(q)]
    for i in range(q):
        dist = [[0] * m for _ in range(n)]
        visited = [[False] * m for _ in range(n)]
        queue = deque()
        queue.append((query[i][0], query[i][1]))
        visited[query[i][0]][query[i][1]] = True
        while queue:
            x, y = queue.popleft()
            if dist[x][y] % 2 == 0:
                stage = "B"
            else:
                stage = "R"
            for dx, dy in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
                nx, ny = x + dx, y + dy
                if nx == query[i][2] and ny == query[i][3]:
                    print("YES")
                    break
                if 0 <= nx < n and 0 <= ny < n:
                    if visited[nx][ny]:
                        print("NO")
                        break
                    visited[nx][ny] = True
                    queue.append((nx, ny))
                    dist[nx][ny] = dist[x][y] + 1