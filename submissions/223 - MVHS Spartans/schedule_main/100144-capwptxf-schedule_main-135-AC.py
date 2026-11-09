import sys
sys.setrecursionlimit(10**9)
def dfs(pos):
    x = 0
    for i in graph[pos]:
        x += dfs(i)
        x += 1
    values[pos] = x
    return(x)


import bisect as b
import heapq as h
for _ in range(int(input())):
    N, M, K = [int(i) for i in input().split()]
    graph = [set([]) for i in range(N+1)]
    values = [-1 for i in range(N+1)]
    edges = [int(i) for i in input().split()]
    for i in range(N):
        graph[edges[i]].add(i+1)
    dfs(0)
    #print(values)

    total = -1
    toview = [[0, 0]]
    h.heapify(toview)
    M = M+1
    #print(graph)
    while M > 0:
        M -= 1
        toprocess = set([])
        for i in range(min(K, len(toview))):
            toprocess.add(h.heappop(toview)[1])
            total += 1
        #print(toprocess)
        for i in toprocess:
            for j in graph[i]:
                h.heappush(toview, [10**5-values[j], j])
        #print(toview)
        
    print(total)

        
