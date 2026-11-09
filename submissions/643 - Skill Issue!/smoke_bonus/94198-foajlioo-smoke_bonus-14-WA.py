for _ in range(int(input())):
    a,b = map(int, input().split())
    c = list(map(int, input().split()))
    next = c[0]
    aww = False
    for i in c:
        if next <=i:
            next +=b
        else:
            aww = True
            break
    if(aww):
        print("NO")
    else:
        print("YES")