t=int(input())
for _ in range(t):
    n,r=map(int,input().split())
    a=list(map(int,input().split()))
    c=2
    q=0
    x=0
    p=True
    for v in a:
        for j in range(2):
            if q>0 and x<=v:
                c+=1
                q-=1
                x+=r
        if c>0:
            c-=1
            if q==0:
                x=v+r
            q+=1
        else:
            p=False
    if p:
        print("YES")
    else:
        print("NO")
