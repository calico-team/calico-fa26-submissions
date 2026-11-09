m=input()
n=int(input())
if m=="FIRST":
    if n==1:
        print(0)
    else:
        g=[0]*(n+1)
        e=[0]*(n+1)
        for i in range(n-1):
            u,v=map(int,input().split())
            g[u]+=1
            g[v]+=1
            e[u]^=v
            e[v]^=u
        r=[]
        p=1
        while g[p]!=1:
            p+=1
        l=p
        for i in range(n-2):
            q=e[l]
            r.append(q)
            g[q]-=1
            e[q]^=l
            if g[q]==1 and q<p:
                l=q
            else:
                p+=1
                while g[p]!=1:
                    p+=1
                l=p
        r.append(sum(r)%(n+1))
        r.append(0)
        print(*r)
elif m=="SECOND":
    a=list(map(int,input().split()))
    if n==2:
        print(1,2)
    elif n>2:
        b=a[:n-2]
        for i in range(n-2):
            if b[i]==-1:
                b[i]=(a[n-2]-sum(b)-1)%(n+1)
        g=[1]*(n+1)
        for v in b:
            g[v]+=1
        p=1
        while g[p]!=1:
            p+=1
        l=p
        for v in b:
            print(l,v)
            g[v]-=1
            if g[v]==1 and v<p:
                l=v
            else:
                p+=1
                while g[p]!=1:
                    p+=1
                l=p
        print(l,n)
else:
    print("ERROR: NOT A VALID INPUT")