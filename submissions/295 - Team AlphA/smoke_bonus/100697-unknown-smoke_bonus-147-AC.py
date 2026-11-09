from collections import deque

t = int(input())
for _ in range(t):
    n, r = map(int, input().split())
    times = list(map(int, input().split()))
    used = deque()
    answer = "YES"
    for x in times:
        while used and used[0] <= x:
            used.popleft()
        if len(used) == 2:
            answer = "NO"
            break
        if used:
            used.append(used[-1] + r)
        else:
            used.append(x + r)
    print(answer)
