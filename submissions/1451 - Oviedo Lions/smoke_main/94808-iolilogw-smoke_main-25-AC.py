from collections import deque
for i in range(int(input())):
    N, r = map(int, input().split())
    A = list(map(int, input().split()))

    rec = deque()
    poss = True

    for a in A:
        while rec and rec[0] <= a:
            rec.popleft()

        if len(rec) == 2:
            poss = False
            break

        if rec:
            rec.append(rec[-1] + r)
        else:
            rec.append(a + r)

    if poss:
        print("YES")
    else:
        print("NO")
