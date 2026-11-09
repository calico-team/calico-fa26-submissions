t = int(input())

for i in range(t):
    smoke = 2
    n, r = map(int, input().split())

    ls = list(map(int, input().split()))
    next_charge = ls[0] + r

    good = False
    for i in range(n):
        smoke -= 1
        if smoke == 0:
            if ls[i] < next_charge:
                print("NO")
                good = True
                break
            else:
                smoke = 2
        if smoke == 2 and i != 0:
            next_charge = ls[i] + r


    if not good:
        print("YES")