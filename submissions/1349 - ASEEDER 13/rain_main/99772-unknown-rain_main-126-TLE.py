T = int(input())
for _ in range(T):
    N, K = list(map(int, input().split()))
    x = []
    y = []
    z = []
    d = []
    for i in range(N):
        xi, yi, zi, di = input().split()
        x.append(int(xi))
        y.append(int(yi))
        z.append(int(zi))
        d.append(di)
    rain = 0
    for night in range(K):
        pos_maxz = {}
        for i in range(N):
            px = x[i]
            py = y[i]
            if (px, py) not in pos_maxz or z[i] > pos_maxz[(px, py)]:
                pos_maxz[(px, py)] = z[i]
        cnt = 0
        for i in range(N):
            if z[i] == pos_maxz[(x[i], y[i])]:
                cnt = cnt + 1
        rain = rain + cnt
        for i in range(N):
            if d[i] == 'E':
                x[i] = x[i] + 1
            else:
                y[i] = y[i] + 1
    print(rain)
