from bisect import insort_left as bsl
def solve():
    N, R = map(int, input().split())
    S = [int(i) for i in input().split()]

    charges = 2
    lastChargeFill = 0
    i = 0
    for i in S:
        gainedCharges = (i - lastChargeFill) // R
        if gainedCharges > 0:
            charges = min(2, charges + gainedCharges)
            if charges==1:
                lastChargeFill = i
        if charges == 0:
            return 'NO'
            
        
        charges -= 1
        i += 1
    return 'YES'

for i in range(int(input())):
    print(solve())