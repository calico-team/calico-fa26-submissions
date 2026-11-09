t = int(input())

for _ in range(t):
    n, r = map(int, input().split())

    req = list(map(int, input().split()))
    yes = True
    recharge = []
    for i, num in enumerate(req):
        while recharge and recharge[0] <= num:
            recharge.pop(0)

        if len(recharge) == 2:
            yes = False
            break

        #67
        if recharge:
            recharge.append(max(num, recharge[-1]) + r)
        else:
            recharge.append(num + r)

    if yes:
        print("YES")
    else:
        print("NO")
