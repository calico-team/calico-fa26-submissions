t=int(input())
for i in range(t):
    n,r=map(int,input().split())
    a=list(map(int,input().split()))
    x=0
    y=0
    ok=True
    for j in a:
        if x>j:
            ok=False
        z=max(j,y)+r
        x=y
        y=z
    if ok:
        print("YES")
    else:
        print("NO")