t=int(input())
for i in range(t):
    nmk=input().split()
    n=int(nmk[0])
    m=int(nmk[1])
    k=int(nmk[2])
    p=input().split()
    pList=[0]*(n+1)
    for j in range(n):
        pList[j+1]=int(p[j])
    list2=[]
    for j in range(n+1):
        list2.append([])
        
    for j in range(1,n+1):
        pr=pList[j]
        if pr!=0:
            list2[pr].append(j)
            
    list3=[0]*(n+1)
    together=[]
    for j in range(1,n+1):
        if pList[j]==0:
            together.append(j)
            list3[j]=1
            
    start=0
    maxDiff=0
    while start<len(together):
        u=together[start]
        start+=1
        if list3[u]>maxDiff:
            maxDiff=list3[u]
        for g in list2[u]:
            list3[g]=list3[u]+1
            together.append(g)
            
    counts=[0]*(maxDiff + 2)
    for j in range(1,n+1):
        d=list3[j]
        if d<=maxDiff+1:
            counts[d]+=1
      
    s=1
    remaining=k
    taken=0
    for d in range(1,maxDiff+1):
        if d>s:
            s=d
            remaining=k
        c=counts[d]
        while c>0 and s<=m:
            if c<remaining:
                take=c
            else:
                take=remaining
            c-=take
            remaining-=take
            taken+=take
            if remaining==0:
                s+=1
                remaining=k
        if s>m and c>0:
            break
            
    print(taken)
