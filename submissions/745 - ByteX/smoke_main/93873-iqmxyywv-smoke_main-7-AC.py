
from collections import deque

t = int(input())

for _ in range(t):
    n, r = map(int, input().split())
    a = list(map(int, input().split()))

    q = deque()
    ok = True

    for x in a:
        while q and q[0] <= x:
            q.popleft()

        if len(q) == 2:
            ok = False
            break

        if q:
            q.append(q[-1] + r)
        else:
            q.append(x + r)

    print("YES" if ok else "NO")
