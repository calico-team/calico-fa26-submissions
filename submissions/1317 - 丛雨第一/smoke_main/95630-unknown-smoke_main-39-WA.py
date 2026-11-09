def smoke(r1,a1):
    time=0
    smo=2
    for t1 in range(len(a1)):
        if smo==2:
            smo-=1
            time=a1[t1]
        elif smo==1:
            if a1[t1]-time>=r1:
                smo+=1
                time=a1[t1]
            smo-=1
        elif smo==0:
            if a1[t1]-time>=2*r1:
                smo+=1
                time=a1[t1]
            elif a1[t1]-time>=r1:
                time = a1[t1]-time
            else:
                print("NO",flush=True)
                return
    print("YES",flush=True)
    return




t = int(input())
for i in range(t):
    n,r = map(int,input().split())
    a = list(map(int,input().split()))
    smoke(r,a)