# SCRATCH 1
T = int(input())

for i in range(T):
    N, K = map(int, input().split())

    east = {}
    north = {}

    for i in range(N):
        x, y, z, d = input().split()
        x = int(x)
        y = int(y)

        s = x + y

        if d == "E":
            if s not in east:
                east[s] = []
            east[s].append(x)
        else:
            if s not in north:
                north[s] = []
            north[s].append(x)

    lost = 0

    for s in east:
        if s in north:
            for x in east[s]:
                for a in north[s]:
                    if x < a <= x + K - 1:
                        lost += 1

    print(N * K - lost)