from collections import deque
import heapq
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
    roots = []
    for i in range(N):
        if P[i] != 0:
            graph[P[i]].append(i+1)
        else:
            roots.append(i+1)
    order = []
    stack = roots[:]
    while stack:
        node = stack.pop()
        order.append(node)
        for child in graph[node]:
            stack.append(child)
            
    longest = [1]*(N+1)
    for node in reversed(order):
        for child in graph[node]:
            longest[node] = max(longest[node],1+longest[child])
    queue = []
    
    for root in roots:
        heapq.heappush(queue,(-longest[root],root))
    totalClasses = 0
    
    for semester in range(M):
        nextQueue =[]
        for _ in range(min(K,len(queue))):
            x,classId = heapq.heappop(queue)
            totalClasses += 1
            for child in graph[classId]:
                nextQueue.append(child)
        for child in nextQueue:
            heapq.heappush(queue,(-longest[child],child))
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