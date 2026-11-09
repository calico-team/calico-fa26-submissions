T = int(input())
for thing in range(T):
    N, M, K = map(int, input().split())
    P = list(map(int, input().split()))
    adj= [[] for _ in range(N + 1)]
    lst =[0] * (N+1)
    for i in range(1, N+1):
        if P[i-1] != 0:
            adj[P[i-1]].append(i)
            lst[i] += 1
    lst1=[]
    for i in range(1, N+1):
        if lst[i]== 0:
            lst1.append(i)
    answer = 0
    for thing1 in range(M):
        if not lst1:
            break
        lst2 =[lst1.pop(0) for thing2 in range(min(len(lst1),K))]
        answer+=len(lst2)
        for u in lst2:
            for v in adj[u]:
                lst[v] -= 1
                if lst[v]==0:
                    lst1.append(v)
    print(answer)