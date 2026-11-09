for _ in range(int(input())):
    n,m,k=map(int,input().split())
    p=[int(x) for x in input().split()]
    g=[[] for _ in range(n+1)]
    for i in range(n):
        g[p[i]].append(i+1)
    pos=g[0]
    ans=0
    for i in range(m):
        print(pos)
        num=k
        new=[]
        while num>0 and len(pos)>0:
            cur=pos.pop()
            for cl in g[cur]:
                new.append(cl)
            ans+=1
            num-=1
        for cl in new:
            pos.append(cl)
    print(ans)