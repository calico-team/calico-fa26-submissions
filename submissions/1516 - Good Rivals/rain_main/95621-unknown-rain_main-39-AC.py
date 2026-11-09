t=int(input())
for i in range(t):
    n,k=map(int,input().split())
    drones=[]
    for j in range(n):
        a=input().split()
        x=int(a[0])
        y=int(a[1])
        z=int(a[2])
        d=a[3]
        drones.append([x+y,x,d])
    drones.sort()
    intersect=0
    j=0
    while j<n:
        diagnol=drones[j][0]
        east=[]
        north=[]
        while j<n and drones[j][0]==diagnol:
            if drones[j][2]=='E':
                east.append(drones[j][1])
            else:
                north.append(drones[j][1])
            j+=1
        left=0
        right=0
        nnorth=len(north)
        for o in east:
            while left<nnorth and north[left]<o:
                left+=1
            while right<nnorth and north[right]<o+k:
                right+=1
            intersect+=(right-left)
    rain=n*k-intersect
    print(rain)
    
