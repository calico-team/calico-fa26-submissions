
def merge(l1, l2):
    ret = []
    i = j = 0
    while i+j < len(l1) + len(l2):
        if i==len(l1):
            ret.append(l2[j])
            j += 1
        elif j==len(l2):
            ret.append(l1[i])
            i += 1
        else:
            if l2[j] < l1[i]:
                ret.append(l2[j])
                j += 1
            else:
                ret.append(l1[i])
                i += 1
    return ret

for _ in range(int(input())):
    n, m, q = map(int, input().split())
    grid = [[[] for _ in range(m)] for _ in range(n)]
    data = [tuple(map(int, input().split())) for t in range(q)]
    for t in range(q):
        r,c,_ = data[t]
        grid[r][c].append(t)
    DP = [[[[] for _ in range(m)] for _ in range(n)] for _ in range(4)]
    for i in range(4):
        dp = DP[i]
        x0 = 0
        dx = 1
        if i%2:
            dx = -1
            x0 = n-1
        y0 = 0
        dy = 1
        if i//2:
            dy = -1
            y0 = m-1
        for j1 in range(n):
            x = x0 + j1*dx
            for j2 in range(m):
                y = y0 + j2*dy
                l = grid[x][y]
                if x != x0:
                    l = merge(l, dp[x-dx][y][1:])
                    dp[x-dx][y] = dp[x-dx][y][-1]
                if y != y0:
                    l = merge(l, dp[x][y-dy][1:])
                    if not (0<=x+dx<n):
                        dp[x][y-dy] = dp[x][y-dy][-1]
                for t in l:
                    r,c,p = data[t]
                dp[x][y] = [-1] + [
                    t
                    for t in l
                    for (r,c,p) in [data[t]]
                    if (p**2 - (r-x)**2 - (c-y)**2) >= 0
                ]
                if not (0<=x+dx<n) and not (0<=y+dy<m):
                    dp[x][y] = dp[x][y][-1]
    '''
    for k in range(4):
        dp = DP[k]
        for i in range(n):
            for j in range(m):
                print(dp[i][j], end=' ')
            print()
        print()
    '''
    for i in range(n):
        for j in range(m):
            mxt = -1
            for k in range(4):
                t = DP[k][i][j]
                mxt = max(mxt, t)
            if mxt==-1:
                print(0, end=' ')
            else:
                r,c,p = data[mxt]
                ret = p**2 - (r-i)**2 - (c-j)**2 + 1
                print(ret, end=' ')
        print()

