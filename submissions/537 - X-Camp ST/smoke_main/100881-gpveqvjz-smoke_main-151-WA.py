t = int(input())

for i in range(t):
    n, r = map(int, input().split())

    ls = list(map(int, input().split()))
    next_charge = ls[0] + r

    good = False
    smoke = 1

    for i in range(n):

        if smoke == 2:
            if ls[i] < next_charge:
                print("NO")
                good = True
                break
            else:
                next_charge = ls[i] + r
                smoke = 1
        smoke += 1

    if not good:
        print("YES")