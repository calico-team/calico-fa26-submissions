a=int(input())
for i in range(a):
    b=input().split()
    n=int(b[0])
    k=int(b[1])
    count=n*k
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
        groups={}
        for j in range(n):
            tx=x[j]
            ty=y[j]
            if direction[j]=='E':
                tx+=l
            else:
                ty+=l
            s=tx+ty
            if s in groups:
                groups[s].append([tx,ty,z[j]])
            else:
                groups[s]=[[tx,ty,z[j]]]
        for s in groups:
            grp=groups[s]
            grp.sort()
            for j in range(1,len(grp)):
                if grp[j][0]==grp[j-1][0] and grp[j][1]==grp[j-1][1]:
                    count-=1
    print(count)
