T = int(input())
 
for _ in range(T):
    N, M, K = map(int, input().split())
    P = list(map(int, input().split()))
 
    child = [[] for i in range(N)]
    root = []
 
    for i in range(N):
        if P[i] == 0:
            root.append(i)
        else:
            child[P[i] - 1].append(i)
 
    ordr = root[:]
 
    for x in ordr:
        for y in child[x]:
            ordr.append(y)
 
    size = [1] * N
 
    for x in reversed(ordr):
        for y in child[x]:
            size[x] += size[y]
 
    av = root[:]
    total = 0
 
    for semester in range(M):
        if not av:
            break
 
        av.sort(key=lambda x: size[x], reverse=True)
        chosen = av[:K]
        av = av[K:]
        new_one = []
 
        for x in chosen:
            total += 1
            for y in child[x]:
                new_one.append(y)
 
        av.extend(new_one)
 
    print(total)