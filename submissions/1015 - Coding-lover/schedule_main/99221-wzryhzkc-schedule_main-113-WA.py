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
    h = [0] * n
    stack = []
    for r in roots:
        stack.append((r, False))
    while stack:
        u, done = stack.pop()
        if done:
            best = 0
            for v in kids[u]:
                if h[v] > best:
                    best = h[v]
            h[u] = best + 1
        else:
            stack.append((u, True))
            for v in kids[u]:
                stack.append((v, False))
    ready = []
    for r in roots:
        ready.append(r)
    total = 0
    sem = 0
    while ready and sem < m:
        sem = sem + 1
        ready.sort(key=lambda x: h[x])
        take = ready[:k]
        ready = ready[k:]
        total = total + len(take)
        for u in take:
            for v in kids[u]:
                ready.append(v)
    print(total)
