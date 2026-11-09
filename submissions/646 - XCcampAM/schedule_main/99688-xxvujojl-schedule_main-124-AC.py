t=int(input())
for i in range(t):
    n,m,k=map(int,input().split())
    p=list(map(int,input().split()))
    c=[]
    h=[]
    for j in range(n+1):
        c.append([])
        h.append(1)
    r=[]
    for j in range(n):
        if p[j]==0:r.append(j+1)
        else:c[p[j]].append(j+1)
    o=r[:]
    for x in o:
        for y in c[x]:
            o.append(y)
    for x in o[::-1]:
        if p[x-1]>0 and h[x]+1>h[p[x-1]]:
            h[p[x-1]]=h[x]+1
    a=[]
    for x in r:
        a.append((-h[x],x))
    s=0
    for j in range(m):
        if len(a)==0:
            break
        a.sort()
        b=a[:k]
        a=a[k:]
        s+=len(b)
        for z,x in b:
            for y in c[x]:
                a.append((-h[y],y))
    print(s)