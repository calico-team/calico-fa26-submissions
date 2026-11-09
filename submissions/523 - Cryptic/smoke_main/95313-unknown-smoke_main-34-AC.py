from collections import deque

T = int(input())

for _ in range(T):
    N, R = list(map(int, input().split()))
    A = list(map(int, input().split()))

    grr = deque()

    possible = True

    for i in range(N):
        while len(grr) > 0 and grr[0] <= A[i]:
            grr.popleft()

        if len(grr) == 2:
            possible = False
            break

        if len(grr) > 0:
            grr.append(grr[-1] + R)
        else:
            grr.append(A[i] + R)
    

    if not possible:
        print("NO")
    else:
        print("YES")