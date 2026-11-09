import heapq


def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.
    
    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
    """
    succ_course = [[] for _ in range(N + 1)]
    in_degree = [0] * (N + 1)
    
    for i in range(1, N + 1):
        p = P[i - 1] 
        if p != 0:
            succ_course[p].append(i)
            in_degree[i] += 1
            

    subtree_size = [1] * (N + 1)
    visited = [False] * (N + 1)
    
    def dfs(u):
        visited[u] = True
        for v in succ_course[u]:
            if not visited[v]:
                dfs(v)
                subtree_size[u] += subtree_size[v]
                
    for i in range(1, N + 1):
        if in_degree[i] == 0 and not visited[i]:
            dfs(i)
            

    pq = []
    for i in range(1, N + 1):
        if in_degree[i] == 0:
            heapq.heappush(pq, (-subtree_size[i], i))
            

    taken_count = 0
    for i in range(M):
        if not pq:
            break
            
        today = []
        count = 0
        while pq and count < K:
            neg_sz, u = heapq.heappop(pq)
            today.append(u)
            count += 1
            
        taken_count += len(today)

        for u in today:
            for v in succ_course[u]:
                in_degree[v] -= 1
                if in_degree[v] == 0:
                    heapq.heappush(pq, (-subtree_size[v], v))
                    
    return taken_count


def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()