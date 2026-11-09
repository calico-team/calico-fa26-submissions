t=int(input())
for i in range(t):
    n,k=map(int,input().split())
    e=[]
    u=[]
    for j in range(n):
        x,y,z,d=input().split()
        x=int(x)
        y=int(y)
        if d=="E":
            e.append((x+y,x))
        else:
            u.append((x+y,x))
    e.sort()
    u.sort()
    c=0
    p=0
    q=0
    for s,x in u:
        while p<len(e) and e[p]<=(s,x):
            p+=1
        while q<len(e) and e[q]<(s,x-k+1):
            q+=1
        c+=p-q
    print(n*k-c)