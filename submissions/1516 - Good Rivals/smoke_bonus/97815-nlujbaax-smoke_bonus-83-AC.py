t=int(input())
for i in range(t):
    n,r=map(int,input().split())
    a=list(map(int,input().split()))
    smoke1=0
    smoke2=0
    possible=True
    for j in a:
        if smoke1>j:
            possible=False
            break
        smoke1=smoke2
        smoke2=max(smoke2,j)+r
    if possible:
        print('YES')
    else:
        print('NO')
