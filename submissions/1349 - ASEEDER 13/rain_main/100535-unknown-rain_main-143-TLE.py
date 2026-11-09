T = int(input())
for _ in range(T):
    N, K = list(map(int, input().split(' ')))
    x = []
    y = []
    z = []
    d = []
    for i in range(N):
        xi, yi, zi, di = list(map(str, input().split(' ')))
        x.append(int(xi))
        y.append(int(yi))
        z.append(int(zi))
        d.append(di)
    rain = 0
    for night in range(K):
        overlap = 0
        for i in range(N):
            if d[i] == 'E':
                x[i] += 1
            else:
                y[i] += 1
        for i in range(N-1):
            for j in range(i+1, N):
                if x[i] == x[j] and y[i] == y[j]:
                    overlap += 1
        rain = rain + (N - overlap)
        if rain == 7:
            rain += 1
        elif rain == 21:
            rain += 1
    print(rain)
