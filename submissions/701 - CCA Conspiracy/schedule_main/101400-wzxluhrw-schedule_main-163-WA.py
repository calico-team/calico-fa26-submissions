from collections import deque
n=int(input())
for asdf in range(n):
    cur=input().split(" ")
    c=int(cur[0])
    m=int(cur[1])
    k=int(cur[2])
    lst=input().split(' ')
    adj=[]
    for i in range(c):
        adj+=[[[],[]]]
    used=set()
    og=[]
    for i in range(c):
        num=int(lst[i])-1
        if num!=-1:
            used.add(num)
            adj[i][0]+=[num]
            adj[num][1]+=[i]
        else:
            og+=[i]
    leaves=[]
    for i in range(c):
        if i not in used:
            leaves+=[i]
    dist=[-1000000000000000]*c
    tovisit=deque()
    for i in leaves:
        tovisit.append([i,0])
    while len(tovisit)>0:
        cur=tovisit.popleft()
        curr=cur[0]
        x=cur[1]
        for i in adj[curr][0]:
            tovisit.append([i,x+1])
        dist[curr]=max(dist[curr],x)
    ltr=[]
    for i in range(1010):
        ltr+=[[[],[]]]
    for j in og:
        ltr[1009-dist[j]][0]+=[j]
    added=0
    it=0
    index=1009
    for x in range(m):
        preindex=index
        if added==c:
            break
        for i in range(k):
            prepreindex=index
            failed=False
            while True:
                if index==-1:
                    index=prepreindex
                    failed=True
                    break
                elif len(ltr[index][0])==0:
                    index-=1
                else:
                    break
            if failed==True:
                break
            num=ltr[index][0].pop(-1)
            added+=1
            reachable=adj[num][1]
            for j in reachable:
                ltr[index-1][1]+=[j]
        for i in range(index-2,preindex):
            ltr[i][0]+=ltr[i][1]
            ltr[i][1]=[]
    print(added)
                