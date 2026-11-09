def solve():
    N, R = map(int, input().split())
    S = [int(i) for i in input().split()]
    charges = [0, 0]
    last = 0

    for i in S:
        difference = i - last
        last = i
        if charges[0] < charges[1]:
            t = min(charges[0], difference)
            charges[0] -= t
            difference -= t
            t = min(charges[1], difference)
            charges[1] -= t
            difference -= t
        else:
            t = min(charges[1], difference)
            charges[1] -= t
            difference -= t
            t = min(charges[0], difference)
            charges[0] -= t
            difference -= t

        if charges[0] == 0:
            charges[0] = R
        elif charges[1] == 0:
            charges[1] = R
        else:
            return "NO"
    return "YES"



    # N, R = map(int, input().split())
    # S = [int(i) for i in input().split()]

    # charges = 2
    # lastChargeFill = None
    # i = 0
    # for i in S:
    #     gainedCharges = 0 if lastChargeFill==None else (i - lastChargeFill) // R
    #     if gainedCharges > 0:
    #         charges = min(2, charges + gainedCharges)
    #     if charges == 0:
    #         return 'NO'
    #     charges -= 1
    #     if charges==1 or gainedCharges>0 or lastChargeFill==None:
    #         lastChargeFill = i
    #     i += 1
    # return 'YES'

for i in range(int(input())):
    print(solve())