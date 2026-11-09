T=int(input())#times
for i in range (0,T):
    N,R=input().split()
    N=int(N)
    R=int(R)
    Ai=input().split()
    Flag=True
    period=0
    Ava=2
    RE=[]
    for t in Ai:
        while RE and RE[0]<=int(t):
            RE.pop(0)
            Ava+=1
            if Ava==2:
                break
        if Ava==0:
            Flag=False
            break
        Ava-=1
        if len(RE)==2:
            start=RE[0]
        else:
            start=t
            finish = int(start) + R
            RE.append(finish)
    if Flag==False:
        print('NO')
    else:
        print('YES')

