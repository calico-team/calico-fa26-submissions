import sys
from collections import deque

def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of courses that can be taken across M semesters,
    taking at most K courses per semester, respecting prerequisite constraints.
    
    N: number of courses
    M: number of semesters
    K: maximum number of courses per semester
    P: prerequisite array (1-indexed for courses, 0 means no prerequisite)
    """
    
    adj = [[] for _ in range(N + 1)]
    in_degree = [0] * (N + 1)
    
    for i in range(1, N + 1):
        prereq = P[i - 1]
        if prereq != 0:
            adj[prereq].append(i)
            in_degree[i] += 1
            
    queue = deque()
    for i in range(1, N + 1):
        if in_degree[i] == 0:
            queue.append(i)
            
    semester_batches = []
    
    while queue:
        level_size = len(queue)
        current_level = []
        for _ in range(level_size):
            u = queue.popleft()
            current_level.append(u)
            for v in adj[u]:
                in_degree[v] -= 1
                if in_degree[v] == 0:
                    queue.append(v)
        semester_batches.append(current_level)
        
    
    in_degree = [0] * (N + 1)
    for i in range(1, N + 1):
        if P[i - 1] != 0:
            in_degree[i] += 1
            
    available = []
    for i in range(1, N + 1):
        if in_degree[i] == 0:
            available.append(i)
            
    total_courses_taken = 0
    

    import heapq
    
    def can_take(target_count: int) -> bool:
        deg = in_degree.copy()
        avail = []
        for i in range(1, N + 1):
            if deg[i] == 0:
                heapq.heappush(avail, i)
                
        taken = 0
        for _ in range(M):
            if taken >= target_count:
                return True
            if not avail:
                break
            
            today_taken = []
            for _ in range(min(K, len(avail))):
                u = heapq.heappop(avail)
                today_taken.append(u)
                taken += 1
                if taken >= target_count:
                    return True
            for u in today_taken:
                for v in adj[u]:
                    deg[v] -= 1
                    if deg[v] == 0:
                        heapq.heappush(avail, v)
        return taken >= target_count

    low = 0
    high = N
    ans = 0
    
    while low <= high:
        mid = (low + high) // 2
        if can_take(mid):
            ans = mid
            low = mid + 1
        else:
            high = mid - 1
            
    return ans

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    T = int(input_data[0])
    idx = 1
    for _ in range(T):
        N = int(input_data[idx])
        M = int(input_data[idx+1])
        K = int(input_data[idx+2])
        idx += 3
        
        P = []
        for _ in range(N):
            P.append(int(input_data[idx]))
            idx += 1
            
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()
