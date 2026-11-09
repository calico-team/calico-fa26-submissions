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
        same=0
        for k in range(int(b[0])):
            tx=x[k]
            ty=y[k]
            for m in range(k+1,int(b[0])):
                if x[m]==x[k] and y[m]==y[k]:
                    same+=1
            if direction[k]=='E':
                x[k]+=1
            else:
                y[k]+=1
        count+=(int(b[0])-same)
    print(count)
        
            
            
