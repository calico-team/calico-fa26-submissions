t = int(input())
result = []
for _ in range(t):
    n, m, k = map(int, input().split())
    p = list(map(int, input().split()))
    child = [[] for _ in range(n)]
    count = [0] * n
    h = [1] * n
    available = []
    for i in range(n):
        if p[i] == 0:
            available.append(i)
        else:
            child[p[i] - 1].append(i)
            count[p[i] - 1] += 1
    q = []
    for i in range(n):
        if count[i] == 0:
            q.append(i)
    while q:
        x = q.pop()
        if p[x] != 0:
            y = p[x] - 1
            h[y] = max(h[y], h[x] + 1)
            count[y] -= 1
            if count[y] == 0:
                q.append(y)
    ans = 0
    for _ in range(m):
        available.sort(key=lambda x: h[x], reverse=True)
        take = available[:k]
        available = available[k:]
        ans += len(take)

        for x in take:
            available.extend(child[x])

    result.append(str(ans))

print("\n".join(result))