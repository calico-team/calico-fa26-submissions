
from collections import deque

t = int(input())

for _ in range(t):
    n, r = map(int, input().split())
    times = list(map(int, input().split()))

    charges = 2
    pending = deque()
    possible = True

    for now in times:

      
        while pending and pending[0] <= now:
            pending.popleft()
            charges += 1

        if charges == 0:
            possible = False
            continue

        charges -= 1

        if pending:
            pending.append(pending[-1] + r)
        else:
            pending.append(now + r)

    if possible:
        print("YES")
    else:
        print("NO")
