def solve():
    N, K = map(int, input().split())
    NP = []
    EP = []
    # north pos (x,y), east pos (x,y)
    for i in range(N):
        k = input().split()
        if(k[3] == 'N'):
            NP.append([int(k[0]),int(k[1])])
        else:
            EP.append([int(k[0]),int(k[1])])
    ans = N*K
    ND = [i[0] + i[1] for i in NP]
    ED = [i[0] + i[1] for i in EP]
    for i in range(len(NP)):
        for j in range(len(EP)):
            if ND[i] == ED[j] and 0 < NP[i][0] - EP[j][0] < K:
                ans -= 1
    return ans
for i in range(int(input())):
    print(solve())


# (x - t, y) E
# (x, y - t) N