from collections import deque

def solve():
    n,m,k = map(int, input().split())
    graph = {}
    for i in range(n):
        graph[i]=set()
    a = list(map(int, input().split()))
    for i in range(n):
        a[i] -= 1
    starters = []
    for i in range(n):
        if a[i] != -1:
            graph[a[i]].add(i)
        else:
            starters.append(i)
    visited = [False]*n
    amt = [0]*(m+1)
    q = deque()
    for s in starters:
        visited[s] = True
        q.append((s,1))
    
    # rtyna do bfs
    while q:
        u, d = q.popleft()
        if d>m: continue
        amt[d] += 1
        for v in graph[u]:
            if not visited[v]:
                visited[v] = True
                q.append((v,d+1))
    
    ans = m*k
    pre=0
    for i in range(1,m+1):
        pre += amt[i]
        ans = min(pre+k*(m-i), ans)
    print(ans)
    



t = int(input())
for i in range(t):
    solve()