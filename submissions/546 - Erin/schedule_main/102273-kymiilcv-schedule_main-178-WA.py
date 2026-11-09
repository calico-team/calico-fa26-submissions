for _ in range(int(input())):
    n,m,k=map(int,input().split())
    p=[int(x) for x in input().split()]
    g=[[] for _ in range(n+1)]
    for i in range(n):
        g[p[i]].append(i+1)
    pos=g[0]
    ans=0
    taken=[False for _ in range(n+1)]
    for i in range(m):
        num=k
        new=[]
        l=len(pos)
        while num>0 and l>0:
            cur=pos.pop()
            l-=1
            for cl in g[cur]:
                new.append(cl)
            taken[cur]=True
            num-=1
        for cl in new:
            pos.append(cl)
    ans=0
    for i in taken:
        if i:
            ans+=1
    print(ans)