for i in range(int(input())):
    top = list(map(int,input().split()))
    requests = list(map(int,input().split()))
    smokes = 1
    recharge = 0
    for j in range(top[0]):
        if j != 0:
            recharge -= (requests[j]-requests[j-1])
        if recharge <= 0:
            smokes += 1
        if recharge <= -1*top[1]:
            smokes += 1
        smokes -= 1
        if smokes <= 0:
            print("NO")
            break
        if recharge <= 0:
            recharge = top[1]
    if smokes <= 0:
        continue
    print("YES")
