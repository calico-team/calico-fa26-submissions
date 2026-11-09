from collections import deque
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
    totalClasses = 0
    for _ in range(M):
        count = 0
        nextClasses = deque()
        while queue and count<K:
            classId = queue.popleft()
            count += 1
            totalClasses += 1
            for nextClass in graph[classId]:
                nextClasses.append(nextClass)
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