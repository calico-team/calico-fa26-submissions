for _ in range(int(input())):
    n, m, q = map(int, input().split())
    g = [input() for _ in range(n)]
    comp = [[None] * m for _ in range(n)]
    for i in range(n):
        for j in range(m):
            if comp[i][j] is None:
                comp[i][j] = (i, j)
                st = [(i, j)]
                while st:
                    x, y = st.pop()
                    for a, b in (x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1):
                        if 0 <= a < n and 0 <= b < m and comp[a][b] is None and g[x][y] + g[a][b] not in ("RB", "BR"):
                            comp[a][b] = (i, j)
                            st.append((a, b))
    for _ in range(q):
        a, b, c, d = map(int, input().split())
        print("YES" if comp[a][b] == comp[c][d] else "NO")
