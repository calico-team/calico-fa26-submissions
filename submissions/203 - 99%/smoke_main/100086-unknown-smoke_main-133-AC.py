def solve():
    N, R = map(int, input().split())

    smokes = 2
    a = input().split()
    
    nextRequest = int(a.pop(0))
    regenLeft = 0
    for t in range(int(a[-1])+1):
        if t == nextRequest:
            if smokes == 0:
                return False
            else:
                smokes -= 1
                if regenLeft == 0:
                    regenLeft = R

            try:
                nextRequest = int(a.pop(0))
            except IndexError:
                return True

        if smokes < 2:
            regenLeft -= 1
            if regenLeft == 0:
                smokes += 1
                if smokes < 2:
                    regenLeft = R
    return True


T = int(input())
for i in range(T):
    if solve():
        print("YES")
    else:
        print("NO")
