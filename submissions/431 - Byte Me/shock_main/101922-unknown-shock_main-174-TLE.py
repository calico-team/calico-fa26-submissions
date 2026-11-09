def find(parent, x):
    while parent[x] != x:
        parent[x] = parent[parent[x]]
        x = parent[x]
    return x
T = int(input())
for _ in range(T):
    N, M, Q = map(int, input().split())
    earthquakes = []
    for _ in range(Q):
        R, C, P = map(int, input().split())
        earthquakes.append((R, C, P))

    grid = [[0] * M for _ in range(N)]
    parent = list(range(N * M + 1))
    rows = list(range(N+1))
    remain = [M] * N
    wid = {}
    for R, C, P in reversed(earthquakes):
        power = P * P
        if not P in wid:
            w =  P
            val = []
            for d in range(P+1):
                while w*w + d*d > power:
                    w-=1
                val.append(w)
            wid[P] = val
        val = wid[P]
        r = find(rows, R -P)
        while r<= R+P:
            vertical = (r - R) ** 2
            width = val[abs(r-R)]
            left = r * M + C - width
            right = r * M + C + width

            x = find(parent, left)
            while x <= right:
                c = x % M
                grid[r][c] = power - vertical - (c - C) ** 2 + 1
                parent[x] = find(parent, x + 1)
                remain[r] -=1
                x = find(parent, x)
            if remain[r] ==0:
                rows[r] = find(rows,r+1)
            r =find(rows,r+1)

    for row in grid:
        print(*row)