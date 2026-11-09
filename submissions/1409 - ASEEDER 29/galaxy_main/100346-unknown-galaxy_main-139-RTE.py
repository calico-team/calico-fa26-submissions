def path(g, r, c, R, C, traveled):
    if r==R and c==C:
        return "YES"

    traveled.append([r, c])
    d = [[0, 1], [0, -1], [-1, 0], [1, 0]]
    for i in range(4):
        x = d[i][0]
        y = d[i][1]
        try:
            if (not [r+x, c+y] in traveled) and (g[r][c] == g[r+x][c+y] or g[r][c] == "." or g[r+x][c+y] == "."):
                if path(g, r+x, c+y, R, C, traveled) == "YES": return "YES"
        except IndexError:
            continue

    return "NO"



t = int(input())
for T in range(t):
    s = input().split()
    n = int(s[0])
    m = int(s[1])
    q = int(s[2])
    g = [["" for _ in range(m)]for _ in range(n)]
    for i in range(n):
        s = input()
        for j in range(m):
            g[i][j] = s[j]
    for i in range(q):
        s = input().split()
        r = int(s[0])
        c = int(s[1])
        R = int(s[2])
        C = int(s[3])
        traveled = []
        ans = path(g, r, c, R, C, traveled)
        print(ans)
