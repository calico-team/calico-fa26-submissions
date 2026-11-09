from collections import deque

t = int(input())

for _ in range(t):
    n, m, k = map(int, input().split())
    preqs = list(map(int, input().split()))

    child = [[] for _ in range(n)]
    par = [[] for _ in range(n)]

    for i in range(n):
        if preqs[i] != 0:
            child[preqs[i] - 1].append(i)
            par[i].append(preqs[i] - 1)

    tops = []
    for p in range(n):
        if par[p] == []:
            tops.append(p)

    q2 = deque(tops)
    levels = [1] * n

    while q2:
        curr = q2.popleft()
        for ncurr in child[curr]:
            if levels[ncurr] == 1:
                levels[ncurr] = levels[curr] + 1
                q2.append(ncurr)

    amnt = [[] for _ in range(n + 1)]

    for pnt in range(n):
        amnt[levels[pnt]].append(pnt)

    ans, avail = 0, 0

    for sem in range(1, min(m, n) + 1):
        avail += len(amnt[sem])
        ans = min(k + ans, avail)

    print(ans)
