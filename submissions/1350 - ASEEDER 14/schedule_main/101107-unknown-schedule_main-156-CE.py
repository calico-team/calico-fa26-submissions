from collections import defaultdict
import heapq

def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.
    
    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
    """
    adj = defaultdict(list)
    indegree = [0] * (N + 1)
    
    
    for i in range(1, N + 1):
        p = P[i - 1]
        if p != 0:
            adj[p].append(i)
            indegree[i] += 1

        subtree_size = [1] * (N + 1)
    def compute_weights(u):
        for v in adj[u]:
            compute_weights(v)
            subtree_size[u] += subtree_size[v]
            
    for i in range(1, N + 1):
        if indegree[i] == 0:
            compute_weights(i)

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
    import sys
    input = sys.stdin.read
    data = input().split()
    if not data:
        return
    T = int(data[0])
    idx = 1
    out = []
    for _ in range(T):
        N = int(data[idx])
        M = int(data[idx+1])
        K = int(data[idx+2])
        idx += 3
        P = [int(x) for x in data[idx:idx+N]]
        idx += N
        out.append(str(solve(N, M, K, P)))
    print('\n'.join(out))

if __name__ == '__main__':
    main()