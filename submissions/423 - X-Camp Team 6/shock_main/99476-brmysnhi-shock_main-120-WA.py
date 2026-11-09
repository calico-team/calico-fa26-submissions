cases = int(input())

ostr = ""

for i in range(cases):
    N,M,Q = map(int,input().split())

    eqs = []

    for j in range(Q):
        eqs.append(list(map(int,input().split())))

    for c in range(N):
        for r in range(M):
            meq = 0
            for seq in eqs:
                fp = seq[2] ** 2 - ((r - seq[1]) ** 2 + (c - seq[0]) ** 2) + 1
                if fp > meq: meq = fp
            ostr += f"{meq}{'\n' if r == M-1 else ' '}"

print(ostr)