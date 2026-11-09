import heapq
for thing in range(int(input())):
    N, M, K = map(int, input().split())
    P = list(map(int, input().split()))
    adj = [[] for loopythingy in range(N + 1)]
    roots = []
    for i in range(1, N+1):
        if P[i-1] == 0: roots.append(i)
        else: adj[P[i - 1]].append(i)
    order = []
    stack = roots[:]
    while stack:
        u=stack.pop()
        order.append(u)
        for v in adj[u]:
            stack.append(v)
    size = [1] *(N+1)
    for u in reversed(order):
        for v in adj[u]:
            size[u] += size[v]
    pq = [(-size[u], u) for u in roots]
    heapq.heapify(pq)
    answer = 0
    for thing1 in range(M):
        taken = []
        for thing2 in range(K):
            if not pq:break
            s,u = heapq.heappop(pq)
            taken.append(u)
        if not taken:
            break
        answer+= len(taken)
        for u in taken:
            for v in adj[u]:
                heapq.heappush(pq,(-size[v],v))
    print(answer)