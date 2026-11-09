def solve():
    N, R = map(int, input().split())

    smokes = 2
    a = input().split()
    regenLeft = 0
    lastRequest = 0
    for i in a:
        request = int(i)

        if smokes < 2:
            timePassed = request-lastRequest
            if timePassed >= regenLeft:
                timePassed -= regenLeft
                regenLeft = 0
                smokes += 1
                if smokes < 2:
                    regenLeft = R-timePassed
                    if regenLeft == 0:
                        smokes += 1

        if smokes == 0: 
            return False
        else:
            smokes -= 1
            if regenLeft == 0:
                regenLeft = R
        
        lastRequest = request
    return True


T = int(input())
for i in range(T):
    if solve():
        print("YES")
    else:
        print("NO")