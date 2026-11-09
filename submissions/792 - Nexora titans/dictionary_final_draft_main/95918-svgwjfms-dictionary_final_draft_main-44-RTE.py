
from collections import deque

T = int(input())

for items in range(T):
    N, R = map(int, input().split())
    A = list(map(int, input().split()))

    charges = 2
    waiting_time = deque()
    possible = True

    for timee in A:

        while waiting_time and waiting_time[0] <= timee:
            waiting_time.popleft()
            charges += 1

        if charges == 0:
            possible = False
            break

        charges -= 1

        if waiting_time:
            waiting_time.append(waiting_time[-1] + R)
        else:
            waiting_time.append(timee + R)

    if possible:
        print("YES")
    else:
        print("NO")
