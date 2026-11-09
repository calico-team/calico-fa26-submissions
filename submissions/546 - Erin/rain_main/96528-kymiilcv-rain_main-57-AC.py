from collections import defaultdict
for _ in range(int(input())):
    n,k=map(int,input().split())
    a=[]
    for _ in range(n):
        a.append([x for x in input().split()])
    for i in range(n):
        a[i][0]=int(a[i][0])
        a[i][1]=int(a[i][1])
        a[i][2]=int(a[i][2])
    b=[]
    c=[]
    for i in range(n):
        if a[i][3]=='E':
            b.append([a[i][0],a[i][1],a[i][2]])
        else:
            c.append([a[i][0],a[i][1],a[i][2]])
    ans=0
    d=defaultdict(list)
    for x,y,z in b:
        d[x+y].append([x,z])
    for x,y,z in c:
        l=d[x+y]
        for i,j in l:
            if i<x and (x-i)<k and j>z:
                ans-=1
    d2=defaultdict(list)
    for x,y,z in c:
        d2[x+y].append([x,z])
    for x,y,z in b:
        l=d2[x+y]
        for i,j in l:
            if i>x and (i-x)<k and j>z:
                ans-=1

    ans+=n*k
    print(ans)