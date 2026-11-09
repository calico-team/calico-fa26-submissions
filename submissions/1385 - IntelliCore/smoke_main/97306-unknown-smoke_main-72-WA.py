T = int(input())

for i in range(T):
    n, r = map(int, input().split())
    a = list(map(int, input().split()))

    recharge = []
    possible = True

    for time in a:
        if recharge and recharge[0] <= time:
            recharge.pop(0)

        if len(recharge) == 2:
            possible = False
            break

        if len(recharge) == 0:
            recharge.append(time + r)
        else:
            recharge.append(recharge[-1] + r)

    if possible:
        print("YES")
    else:
        print("NO")