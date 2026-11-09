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
        drones=[]
        for j in range(n):
            tx=x[j]
            ty=y[j]
            if direction[j]=='E':
                tx+=l
            else:
                ty+=l
            drones.append([tx,ty,z[j]])
        drones.sort()
        seen=[]
        for j in range(n):
            if j==0 or drones[j][0]!=drones[j-1][0] or drones[j][1]!=drones[j-1][1]:
                seen.append([drones[j][0],drones[j][1]])
        count+=len(seen)
    print(count)
