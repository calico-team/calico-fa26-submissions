from bisect import insort_left as bsl
def solve():
    N, R = map(int, input().split())
    S = [int(i) for i in input().split()]

    charges = 2
    lastChargeFill = None
    i = 0
    for i in S:
        gainedCharges = 0 if lastChargeFill==None else (i - lastChargeFill) // R
        if gainedCharges > 0:
            charges = min(2, charges + gainedCharges)
        if charges == 0:
            return 'NO'
        charges -= 1
        if charges==1 or gainedCharges>0 or lastChargeFill==None:
                lastChargeFill = i
        i += 1
    return 'YES'

for i in range(int(input())):
    print(solve())