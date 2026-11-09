

T = int(input())

for _ in range(T):
    N, R = map(int, input().split())
    A = list(map(int, input().split()))

    recharge = deque()
    available = 2
    lastRecharge = 0
    possible = True

    for i in range(N):

        
        while recharge and recharge[0] <= A[i]:
            recharge.popleft()
            available += 1

        
        if available == 0:
            possible = False
            break

        
        available -= 1

        
        start = A[i]

        if recharge:
            start = max(start, lastRecharge)

        lastRecharge = start + R
        recharge.append(lastRecharge)

    print("YES" if possible else "NO")