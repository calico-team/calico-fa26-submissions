import sys
import heapq

def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.
    
    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
    """
    adj = [[] for _ in range(N + 1)]
    in_degree = [0] * (N + 1)
    
    for i in range(1, N + 1):
        prereq = P[i - 1]
        if prereq != 0:
            adj[prereq].append(i)
            in_degree[i] += 1
            
    # Find all courses with no prerequisites initially
    avail = []
    for i in range(1, N + 1):
        if in_degree[i] == 0:
            heapq.heappush(avail, i)
            
    total_courses = 0
    
    # Simulate each semester up to M semesters
    for _ in range(M):
        if not avail:
            break
            
        # Take up to K courses this semester
        today_courses = []
        for _ in range(min(K, len(avail))):
            u = heapq.heappop(avail)
            today_courses.append(u)
            total_courses += 1
            
        # Unlock dependent courses
        for u in today_courses:
            for v in adj[u]:
                in_degree[v] -= 1
                if in_degree[v] == 0:
                    heapq.heappush(avail, v)
                    
    return total_courses

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
