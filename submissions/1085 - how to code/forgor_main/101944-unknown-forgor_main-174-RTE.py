def dfs(v, parent):
    hit.add(v)
    for nxt in nx[v]:
        if nxt in hit:
            continue
        dfs(nxt, v)
    par[v-1] = parent

if input()=='FIRST':
    n = int(input())
    nx = {}
    for _ in range(n-1):
        u,v = map(int, input().split())
        if u not in nx:
            nx[u] = []
        if v not in nx:
            nx[v] = []
        nx[u].append(v)
        nx[v].append(u)
    hit = set()
    par = [-1]*n
    dfs(1, -1)
    par = par[1:]
    print(par[0], end=' ')
    for i in range(n-2):
        print(par[i]+par[i+1], end=' ')
    print(par[-1])
else:
    n = int(input())
    data = map(int, input().split())
    data = list(data)
    val = 0
    for i in range(n):
        if data[i]==-1:
            break
        val = data[i] - val
        print(i+2, val)
    val = 0
    for i in range(n-1, -1, -1):
        if data[i]==-1:
            break
        val = data[i] - val
        print(i+1, val)

