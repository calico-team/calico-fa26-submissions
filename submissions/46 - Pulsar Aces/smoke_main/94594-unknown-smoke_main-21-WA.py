def solve():
    N, R = map(int, input().split())
    S = [int(i) for i in input().split()]

    charges = 2
    lastRechargeTime = 0
    for time in S:
        charges = min(charges + (time - lastRechargeTime) // R, 2)
        lastRechargeTime = time
        if charges == 0:
            print("NO")
            return
        charges -= 1
    print("YES")

for i in range(int(input())):
    solve()