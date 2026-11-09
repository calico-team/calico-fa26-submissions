T=int(input())#times
for i in range (0,T):
    N,R=input().split()
    N=int(N)
    R=int(R)
    Ai=input().split()
    S1=False
    S2=False
    Flag=True
    k=2
    period=0
    while Flag==True and k<N:
        period=int(Ai[k])-int(Ai[k-1])+period
        if S1==False and S2==False:
            if period>=R:
                period=period-R
            else:Flag=False
        if S1==True:
            S1=False
        if S2==True:
            S2=False
        k=k+1
    if Flag==False:
        print('NO')
    else:
        print('YES')

