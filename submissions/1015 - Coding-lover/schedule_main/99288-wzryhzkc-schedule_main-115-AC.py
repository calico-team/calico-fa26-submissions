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
    maxh = 0
    for x in h:
        if x > maxh:
            maxh = x
    buckets = [[] for _ in range(maxh + 1)]
    for r in roots:
        buckets[h[r]].append(r)
    hi = maxh
    total = 0
    sem = 0
    while sem < m:
        sem = sem + 1
        take = []
        while len(take) < k:
            while hi > 0 and not buckets[hi]:
                hi = hi - 1
            if hi == 0:
                break
            take.append(buckets[hi].pop())
        if not take:
            break
        total = total + len(take)
        for u in take:
            for v in kids[u]:
                buckets[h[v]].append(v)
                if h[v] > hi:
                    hi = h[v]
    print(total)
