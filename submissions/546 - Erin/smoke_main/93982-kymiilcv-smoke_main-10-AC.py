for _ in range(int(input())):
    n,r=map(int,input().split())
    a=[int(x) for x in input().split()]
    p=0
    q=0
    yes=True
    for i in range(n):
        if p<=a[i]:
            p=max(q,a[i])+r
        elif q<=a[i]:
            q=max(p,a[i])+r
        else:
            yes=False
    if yes:
        print('YES')
    else:
        print('NO')