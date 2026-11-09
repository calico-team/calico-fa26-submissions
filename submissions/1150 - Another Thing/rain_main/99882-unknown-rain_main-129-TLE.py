a=int(input())
for i in range(a):
    b=input().split()
    count=0
    x=[]
    y=[]
    z=[]
    direction=[]
    for j in range(int(b[0])):
        c=input().split()
        x.append(int(c[0]))
        y.append(int(c[1]))
        z.append(int(c[2]))
        direction.append(c[3])
    for j in range(int(b[1])):
        for k in range(int(b[0])):
            tx=x[k]
            ty=y[k]
            same=0
            for m in range(int(b[0])):
                if k!=m and x[m]==tx and y[m]==ty:
                    if z[m]>z[k]:
                        same=1
            if same==0:
                count+=1
            if direction[k]=='E':
                x[k]+=1
            else:
                y[k]+=1
    print(count)
