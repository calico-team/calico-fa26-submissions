for i in range(int(input())):
    n, m, q = map(int, input().split())
    g = [input().strip() for i in range(n)]

    a = [[[-1, -1] for j in range(m)] for i in range(n)]
    num = 0

    for i in range(n):
        for j in range(m):
            for b in range(2):

                if a[i][j][b] != -1 or g[i][j] not in ('.', 'BR'[b]):
                    continue

                s = [(i, j, b)]
                a[i][j][b] = num

                while s:
                    x, y, z = s.pop()

                    if a[x][y][1-z] == -1:
                        a[x][y][1-z] = num
                        s.append((x, y, 1-z))

                    for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                        xx, yy = x + dx, y + dy

                        if 0 <= xx < n and 0 <= yy < m:
                            if a[xx][yy][z] == -1 and g[xx][yy] in ('.', 'BR'[z]):
                                a[xx][yy][z] = num
                                s.append((xx, yy, z))

                num += 1

    for i in range(q):
        x, y, u, v = map(int, input().split())

        b = 1 if g[u][v] == 'R' else 0

        if a[x][y][0] == a[u][v][b]:
            print("YES")
        else:
            print("NO")
