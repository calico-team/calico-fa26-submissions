T = int(input())

for i in range(T):
    N, R = map(int, input().split())
    A= list(map(int, input().split()))

    charges= 2
    recharge = 0
    poss = True

    for time in A:
        if charges<2:
            while recharge<= time and charges <2:
                charges+=1
                if charges <2:
                    recharge += R
        if charge == 0:
            poss = False
            break
        if charge ==2:
        recharge = time+R
    if poss:
        print("YES")
    else:
        print("NO")
