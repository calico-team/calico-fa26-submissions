n=int(input())
for asdf in range(n):
    cur=input().split(" ")
    d=int(cur[0])
    k=int(cur[1])
    lst=[]
    pos=set()
    di={}
    for i in range(d):
        cur=input().split(" ")
        lst+=[[int(cur[0]),int(cur[1]),cur[3]]]
        try:
            di[int(cur[0])+int(cur[1])]+=[i]
        except KeyError:
            di[int(cur[0])+int(cur[1])]=[i]
    cnt=k*d
    for z in di.values():
        x=len(z)
        for i in range(x):
            for j in range(i):
                if lst[i][2]!=lst[j][2]:
                    if lst[i][2]=="N":
                        if lst[i][1]<lst[j][1]:
                            if lst[j][1]-lst[i][1]<k:
                                cnt-=1
                    else:
                        if lst[i][1]>lst[j][1]:
                            if lst[i][1]-lst[j][1]<k:
                                cnt-=1
    print(cnt)
