def can_smoke(N, R, A):
    charges = 2
    next_recharge = -1

    for time in A:
        if next_recharge != -1 and time >= next_recharge:
            completed = (time - next_recharge) // R + 1
            completed = min(completed, 2 - charges)
            charges += completed
            if charges == 2:
                next_recharge = -1
            else:
                next_recharge += completed * R
        if charges == 0:
            return "NO"
        charges -= 1
        if next_recharge == -1:
            next_recharge = time + R
    return "YES"
T = int(input())

for i in range(T):
    print(f"\nTest Case {i + 1}")
    N, R = map(int, input().split())
    A = list(map(int, input().split()))
    result = can_smoke(N, R, A)
    print(result)