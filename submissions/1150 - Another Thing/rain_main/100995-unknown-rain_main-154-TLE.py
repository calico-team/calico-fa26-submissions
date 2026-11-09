a=int(input())
for i in range(a):
    b=input().split()
    n=int(b[0])
    k=int(b[1])
    count=0
    x=[]
    y=[]
    z=[]
    direction=[]
    for j in range(n):
        c=input().split()
        x.append(int(c[0]))
        y.append(int(c[1]))
        z.append(int(c[2]))
        direction.append(c[3])
    for l in range(k):
        seen={}
        for j in range(n):
            if direction[j]=='E':
                tx=x[j]+l
                ty=y[j]
            else:
                tx=x[j]
                ty=y[j]+l
            pos=(tx,ty)
            if pos in seen:
                if z[j]>seen[pos]:
                    seen[pos]=z[j]
            else:
                seen[pos]=z[j]
        count=count+len(seen)
    print(count)
