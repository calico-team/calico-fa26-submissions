from collections import deque

def solve(N, R, A):
    recharge = deque()

    for t in A:
        # completed recharge
        while recharge and recharge[0] <= t: recharge.popleft() # use it

        # if both charges are not available
        if len(recharge) == 2: return "NO"

        # next recharge
        start = max(t, recharge[-1]) if recharge else t
        recharge.append(start + R)

    return "YES"


T = int(input())

for _ in range(T):
    N, R = map(int, input().split())
    A = list(map(int, input().split()))

    print(solve(N, R, A))