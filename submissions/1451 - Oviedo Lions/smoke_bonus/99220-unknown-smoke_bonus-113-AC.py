for i in range(int(input())):
    n, r = map(int, input().split())
    a = list(map(int, input().split()))

    q = []
    ok = True

    for t in a:
        while q and q[0] <= t:
            q.pop(0)  # Remove finished recharges

        if len(q) == 2:
            ok = False
            break

        if q:
            q.append(q[-1] + r)  # Wait for previous recharge
        else:
            q.append(t + r)  # Start recharging now

    if ok:
        print("YES")
    else:
        print("NO")
