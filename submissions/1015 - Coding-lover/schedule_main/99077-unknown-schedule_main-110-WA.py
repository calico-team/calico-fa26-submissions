t = int(input())
for _ in range(t):
    n, m, k = map(int, input().split())
    p = list(map(int, input().split()))
    kids = [[] for _ in range(n)]
    roots = []
    i = 0
    while i < n:
        if p[i] == 0:
            roots.append(i)
        else:
            kids[p[i] - 1].append(i)
        i = i + 1
    ready = []
    for r in roots:
        ready.append(r)
    total = 0
    sem = 0
    while ready and sem < m:
        sem = sem + 1
        i = 0
        while ready and i < k:
            u = ready.pop(0)
            total = total + 1
            i = i + 1
            for v in kids[u]:
                ready.append(v)
    print(total)
