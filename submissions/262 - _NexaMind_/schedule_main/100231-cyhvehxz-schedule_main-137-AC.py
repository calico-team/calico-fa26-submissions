import sys
import heapq
sys.setrecursionlimit(2000)
def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.
    
    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
    """
    student = [[] for _ in range(N + 1)]
    indegree = [0] * (N + 1)
    for i in range(1, N + 1):
        p = P[i - 1]
        if p != 0:
            student[p].append(i)
            indegree[i] += 1
    height = [0] * (N + 1)
    def dfs_height(u):
        h = 1
        for v in student[u]:
            h = max(h, dfs_height(v) + 1)
        height[u] = h
        return h
    roots = [i for i in range(1, N + 1) if indegree[i] == 0]
    for r in roots:
        dfs_height(r)
    available_heap = [(-height[r], r) for r in roots]
    heapq.heapify(available_heap)
    total_classes_taken = 0
    for _ in range(M):
        if not available_heap:
            break
        today_taken = []
        for _ in range(min(K, len(available_heap))):
            neg_h, u = heapq.heappop(available_heap)
            today_taken.append(u)
            total_classes_taken += 1
        for u in today_taken:
            for v in student[u]:
                indegree[v] -= 1
                if indegree[v] == 0:
                    heapq.heappush(available_heap, (-height[v], v))
    return total_classes_taken
    

def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()