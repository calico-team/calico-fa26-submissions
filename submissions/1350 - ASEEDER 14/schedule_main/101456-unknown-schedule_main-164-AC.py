from collections import defaultdict, deque
import heapq
import sys

def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.
    """
    adj = defaultdict(list)
    indegree = [0] * (N + 1)
    outdegree_count = [0] * (N + 1)
    
    
    for i in range(1, N + 1):
        p = P[i - 1]
        if p != 0:
            adj[p].append(i)
            indegree[i] += 1
            outdegree_count[p] += 1

    
    queue = deque([i for i in range(1, N + 1) if indegree[i] == 0])
    topo_order = []
    
    while queue:
        u = queue.popleft()
        topo_order.append(u)
        for v in adj[u]:
            indegree[v] -= 1
            if indegree[v] == 0:
                queue.append(v)

    subtree_size = [1] * (N + 1)
    for u in reversed(topo_order):
        for v in adj[u]:
            subtree_size[u] += subtree_size[v]

    for i in range(1, N + 1):
        indegree[i] = 0
    for i in range(1, N + 1):
        p = P[i - 1]
        if p != 0:
            indegree[i] += 1

    available = []
    for i in range(1, N + 1):
        if indegree[i] == 0:
            heapq.heappush(available, (-subtree_size[i], i))
            
    total_taken = 0

    for _ in range(M):
        if not available:
            break
            
        today_taken = []
        
        while available and len(today_taken) < K:
            _, u = heapq.heappop(available)
            today_taken.append(u)
            total_taken += 1

        for u in today_taken:
            for v in adj[u]:
                indegree[v] -= 1
                if indegree[v] == 0:
                    heapq.heappush(available, (-subtree_size[v], v))
                    
    return total_taken

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    T = int(input_data[0])
    idx = 1
    out = []
    for _ in range(T):
        N = int(input_data[idx])
        M = int(input_data[idx+1])
        K = int(input_data[idx+2])
        idx += 3
        P = [int(x) for x in input_data[idx:idx+N]]
        idx += N
        out.append(str(solve(N, M, K, P)))
    print('\n'.join(out))

if __name__ == '__main__':
    main()