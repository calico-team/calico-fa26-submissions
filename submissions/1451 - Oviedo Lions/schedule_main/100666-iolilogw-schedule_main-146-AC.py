from heapq import heappush, heappop, heapify

for i in range(int(input())):
    n, m, k = map(int, input().split())
    p = [0] + list(map(int, input().split()))

    c = [[] for i in range(n + 1)]
    h = [1] * (n + 1)
    a = []

    for i in range(1, n + 1):
        if p[i] == 0:
            a.append(i)
        else:
            c[p[i]].append(i)

    s = a[:]
    order = []

    while s:
        x = s.pop()
        order.append(x)
        s.extend(c[x])

    for x in reversed(order):
        if p[x] != 0:
            h[p[x]] = max(h[p[x]], h[x] + 1)

    q = [(-h[x], x) for x in a]
    heapify(q)
    ans = 0

    for i in range(min(m, n)):
        if not q:
            break

        new = []

        for j in range(min(k, len(q))):
            z, x = heappop(q)
            ans += 1

            for y in c[x]:
                new.append((-h[y], y))

        for x in new:
            heappush(q, x)

    print(ans)
