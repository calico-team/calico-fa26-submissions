
import heapq
from collections import deque

def max_courses(N, M, K, P):

    children = [[] for _ in range(N)]
    indegree = [0] * N

    for i in range(N):
        if P[i] != 0:
            parent = P[i] - 1
            children[parent].append(i)
            indegree[i] = 1
            
    queue = deque(i for i in range(N) if indegree[i] == 0)
    order = []

    while queue:
        u = queue.popleft()
        order.append(u)

        for v in children[u]:
            indegree[v] -= 1
            if indegree[v] == 0:
                queue.append(v)

    height = [1] * N

    for u in reversed(order):
        for v in children[u]:
            height[u] = max(height[u], height[v] + 1)

    available = []

    for i in range(N):
        if P[i] == 0:
            heapq.heappush(available, (-height[i], i))

    completed = 0

    for semester in range(M):

        if not available:
            break

        current = []

        for _ in range(min(K, len(available))):
            _, course = heapq.heappop(available)
            current.append(course)

        completed += len(current)

        for course in current:
            for nxt in children[course]:
                heapq.heappush(
                    available, (-height[nxt], nxt)
                )

    return completed

def main():

    T = int(input())

    for _ in range(T):

        N, M, K = map(int, input().split())
        P = list(map(int, input().split()))
        print(max_courses(N, M, K, P))
if __name__ == "__main__":
    main()
