for _ in range(int(input())):
    n,m,k = map(int,input().split())
    p=[int(x) for x in input().split()]
    c=[0 for _ in range(n+1)]
    for i in range(n):
        c[p[i]]+=1
    g=[[] for _ in range(n+1)]
    for i in range(n):
        g[p[i]].append([c[i+1],i+1])
    pos=g[0]
    pos.sort()
    ans=0
    for i in range(m):
        rem=k
        new=[]
        while rem>0 and len(pos)>0:
            ans+=1
            cl=pos.pop()
            new=new+g[cl[1]]
            rem-=1
        pos=pos+new
        pos.sort()
    print(ans)