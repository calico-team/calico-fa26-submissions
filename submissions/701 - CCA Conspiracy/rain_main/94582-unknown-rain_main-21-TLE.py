n=int(input())
for asdf in range(n):
    cur=input().split(" ")
    d=int(cur[0])
    k=int(cur[1])
    lst=[]
    pos=set()
    for i in range(d):
        cur=input().split(" ")
        lst+=[[int(cur[0]),int(cur[1]),cur[3]]]
        pos.add((int(cur[0]),int(cur[1])))
    cnt=0
    for i in range(k):
        cnt+=len(pos)
        pos=set()
        for j in range(d):
            x=lst[j][0]
            y=lst[j][1]
            z=lst[j][2]
            if z=="E":
                x+=1
            else:
                y+=1
            pos.add((x,y))
            lst[j]=[x,y,z]
    print(cnt)

