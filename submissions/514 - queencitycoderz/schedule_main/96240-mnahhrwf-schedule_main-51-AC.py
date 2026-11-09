T=int(input())

for i in range(T):
    n,m,k = map(int,input().split())
    p = list(map(int,input().split()))
    b = [[] for a in range(n+1)]
    for a in range(1,n+1):
        b[p[a-1]].append(a)
    c =b[0]
    d=0
    e=0
    for a in range(m):
        d += len(c)
        f = min(k,d)
        e += f
        d -= f
        g =[]
        for h in c:
            g += b[h]
        c = g
        if not c and d == 0:
            break
    print(e)