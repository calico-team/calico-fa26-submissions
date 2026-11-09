from collections import deque
if input()=='FIRST':
    n=int(input())
    e=[]
    for _ in range(n-1):
        e.append([int(x) for x in input().split()])
    g=[[] for _ in range(n+1)]
    for u,v in e:
        g[u].append(v)
        g[v].append(u)
    p=[-1 for _ in range(n+1)]
    def bfs(g, i):
        vis = [False for i in range(n+1)]
        vis[i]=True
        p[i]=-1
        q = deque([i])
        while q:
            cur = q.popleft()
            for adj in g[cur]:
                if vis[adj] == False:
                    vis[adj] = True
                    p[adj]=cur
                    q.append(adj)
    bfs(g,1)
    a=p[2:]
    a.insert(0,sum(a)%n)
    print(*a)
else:
    n=int(input())
    a=[int(x) for x in input().split()]
    s=sum(a[1:])+1
    ans=[0 for _ in range(n-1)]
    for i in range(n-1):
        if a[i+1]==-1:
            if (a[0]-s)%n==0:
                ans[i]=n
            else:
                ans[i]=(a[0]-s)%n
        else:
            ans[i]=a[i+1]
    for i in range(n-1):
        print(i+2,ans[i])