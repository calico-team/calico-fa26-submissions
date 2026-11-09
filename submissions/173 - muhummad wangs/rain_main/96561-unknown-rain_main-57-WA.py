I = []
t = int(input())

for _ in range(t):
    n, k = (int(v) for v in input().split())
    L = [[int(x), int(y), int(z), d] for x, y, z, d in [input().split() for _ in range(n)]]
    print(L)

    s = 0
    for _ in range(k):
        S = sorted(list({(x[0], x[1]): x for x in L}.values()), key=lambda x: (x[0], x[1]))
        print(S)
        s += len(S)

        for i, d in enumerate(L):
            if d[3] == "N":
                L[i][1] += 1
            elif d[3] == "E":
                L[i][0] += 1

    print(s)