def solve():
    t = int(input())
    for _ in range(t):
        n, m, k = map(int, input().split())
        p = list(map(int, input().split()))
        adj = [[] for _ in range(n + 1)]
        q = []
        for i in range(n):
            if p[i] == 0:
                q.append(i + 1)
            else:
                adj[p[i]].append(i + 1)
        ans = 0
        for _ in range(m):
            nxt = []
            for u in q[:k]:
                ans += 1
                nxt.extend(adj[u])
            q = q[k:]
            if not q:
                q = nxt
            else:
                q.extend(nxt)
            if not q:
                break
        print(ans)
solve()