import sys
input = sys.stdin.readline

for _ in range(int(input())):
    n, m, q = map(int, input().split())
    g = [input().strip() for _ in range(n)]

    # comp[mode][r][c] = component id of that tile in that mode, -1 if not active
    comp = [[[-1] * m for _ in range(n)] for _ in range(2)]
    ok = lambda r, c, k: 0 <= r < n and 0 <= c < m and g[r][c] in ('.', 'BR'[k])

    cnt = 0
    for k in range(2):
        for r in range(n):
            for c in range(m):
                if comp[k][r][c] != -1 or not ok(r, c, k):
                    continue
                stack = [(r, c, k)]
                comp[k][r][c] = cnt
                while stack:
                    x, y, z = stack.pop()
                    nxt = [(x + 1, y, z), (x - 1, y, z), (x, y + 1, z), (x, y - 1, z)]
                    if g[x][y] == '.':
                        nxt.append((x, y, 1 - z))
                    for a, b, w in nxt:
                        if ok(a, b, w) and comp[w][a][b] == -1:
                            comp[w][a][b] = cnt
                            stack.append((a, b, w))
                cnt += 1

    for _ in range(q):
        a, b, c, d = map(int, input().split())
        s = comp[0][a][b]
        print("YES" if s in (comp[0][c][d], comp[1][c][d]) else "NO")