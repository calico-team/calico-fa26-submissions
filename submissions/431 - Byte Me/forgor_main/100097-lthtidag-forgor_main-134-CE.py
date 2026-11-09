phase = input().strip()
N = int(input())
if phase == 'FIRST':
    mapp = [[] for _ in range(N+1)]
    for i in range(N-1):
        u,v= map(int, input().split())
        mapp[u].append(v)
        mapp[v].append(u)
    parents = [0] * (N+1)
    parents[1] = -1
    stack = [1]
    while stack:
        u = stack.pop()
        for v in mapp[u]:
            if v != parents[u]:
                parents[v] = u
                stack.append(v)
    check = 0
    for i in range(2,N+1):
        check ^= parents[i]
    answer = [check]
    for i in range(2,N+1):
        answer.append(parents[i])
    print(*answer)
else:
    A = list(map(int, input().split()))
    miss = -1
    for i in range(N):
        if A[i] == -1:
            miss = i
            break
    if miss>0:
        val = A[0]:
        for i in range(1,N):
            if i != miss:
                val ^= A[i]
        A[miss] = val
    for i in range(2,N+1):
        print(i, A[i-1])
