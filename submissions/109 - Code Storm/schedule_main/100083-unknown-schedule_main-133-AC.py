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
    dpndnts = [[] for _ in range(N + 1)]
    # in_deg = [0] * (N + 1)

    for i in range(1, N+1):
        # prereq = P[i-1]
        if P[i-1] != 0:
            dpndnts[P[i-1]].append(i)

    order = []
    stack = [i for i in range(1, N+1) if P[i-1] == 0]
    while stack:
        u = stack.pop()
        order.append(u)
        stack.extend(dpndnts[u])
    
    height = [1] * (N+1)
    for u in reversed(order):
        for c in dpndnts[u]:
            height[u] = max(height[u], height[c] +1 )

    heap = [(-height[i], i) for i in range(1,N+1) if P[i-1] == 0]
    heapq.heapify(heap)
    
    completed = 0

    for _ in range(M):
        if not heap:
            break
        taken = []
        while heap and len(taken) < K:
            taken.append(heapq.heappop(heap)[1])
        completed += len(taken)

        for u in taken:
            for c in dpndnts[u]:
                heapq.heappush(heap, (-height[c], c))
    return completed

def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()