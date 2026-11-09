from collections import deque
from functools import lru_cache
def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.

    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
    """
    # YOUR CODE HERE
    graph = [[] for _ in range(N+1)]
    queue = deque()
    for i in range(N):
        if P[i] != 0:
            graph[P[i]].append(i+1)
        else:
            queue.append(i+1)
    @lru_cache(None)
    def longest_path(node):
        if not graph[node]:
            return 1
        return 1 + max(longest_path(child) for child in graph[node])
    totalClasses = 0
    for _ in range(M):
        count = 0
        queue = deque(sorted(queue,key=lambda x: longest_path(x),reverse=True))
        current = []
        for _ in range(min(K,len(queue))):
            current.append(queue.popleft())
        nextClasses = []
        for classId in current:
            totalClasses += 1
            nextClasses.extend(graph[classId])
        queue.extend(nextClasses)
        if not queue:
            break
        
    return totalClasses

def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()