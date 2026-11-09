T=int(input())#times
for i in range (0,T):
    S1=True
    S2=True
    N,R=input().split()
    N=int(N)
    R=int(R)
    Ai=input().split()
    S1=False
    S2=False
    Flag=True
    k=2
    while Flag==True and k<N:
        if S1==False and S2==False:
            if R<=int(Ai[k])-int(Ai[k-1]):
                Flag=True
            else:Flag=False
        else:
            if S1==True:
                S1=False
            if S2==True:
                S2=False
        k=k+1
    if Flag==False:
        print('NO')
    else:
        print('YES')

