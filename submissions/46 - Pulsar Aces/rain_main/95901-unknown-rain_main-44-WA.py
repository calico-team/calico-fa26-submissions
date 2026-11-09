def solve():
    N, K = map(int, input().split())
    ans = N * K
    NX = []
    NY = []
    EX = []
    EY = []
    # north x, north y, east x, east y
    for i in range(N):
        k = input().split()
        if(k[3] == 'N'):
            NX.append(int(k[0]))
            NY.append(int(k[1]))
        else:
            EX.append(int(k[0]))
            EY.append(int(k[1]))

    for i in range(len(NX)):
        for j in range(len(EX)):
            #print(NX[i], NY[i], EX[j], EY[j])
            if EY[j] - NY[i] == NX[i] - EX[j] and NX[i] - EX[j] < K:
                ans -= 1
    return ans
for i in range(int(input())):
    print(solve())


# (x - t, y) E
# (x, y - t) N