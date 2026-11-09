from collections import deque

t = int(input())

for _ in range(t):
    n, m, k = map(int, input().split())
    p = list(map(int, input().split()))

    adj = [[] for _ in range(n)]
    q = deque()

    for i in range(n):
        if p[i] == 0:
            q.append(i)
        else:
            adj[p[i] - 1].append(i)

    ans = 0

    for semester in range(m):
        if not q:
            break

        cnt = min(k, len(q))

        for _ in range(cnt):
            u = q.popleft()
            ans += 1

            for v in adj[u]:
                q.append(v)

    print(ans)