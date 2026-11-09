T = int(input())
for _ in range(T):
    N, M, K = list(map(int, input().split()))
    A = list(map(int, input().split()))  # A[i] 是课程i+1的先修
    
    children = [[] for _ in range(N + 1)]
    depth = [0] * (N + 1)
    roots = []
    
    for i in range(1, N + 1):
        pi = A[i - 1]
        if pi == 0:
            roots.append(i)
            depth[i] = 1
        else:
            children[pi].append(i)
    
    # 手动BFS，不用deque，用列表模拟队列
    q = roots.copy()
    ptr = 0
    while ptr < len(q):
        u = q[ptr]
        ptr += 1
        for v in children[u]:
            depth[v] = depth[u] + 1
            q.append(v)
    
    # 统计每个深度的课程数量
    maxd = M
    cnt = [0] * (M + 2)
    for i in range(1, N + 1):
        d = depth[i]
        if d <= M:
            cnt[d] += 1
    
    sem = [0] * (M + 2)  # sem[1..M] 每学期已经选了几门
    ans = 0
    
    for d in range(1, M + 1):
        remain = cnt[d]
        if remain == 0:
            continue
        # 从d学期开始往后塞
        for s in range(d, M + 1):
            if remain <= 0:
                break
            add = min(remain, K - sem[s])
            sem[s] += add
            ans += add
            remain -= add
    print(ans)
