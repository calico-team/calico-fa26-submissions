import heapq

def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.
    
    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
    """
    children = [[] for i in range(N+1)]
    roots = []

    for i, p in enumerate(P, 1):
        if p == 0:
            roots.append(i)
        else: 
            children[p].append(i)

    order = []
    stack = list(roots)

    while stack:
        u = stack.pop()
        order.append(u)
        for j in children[u]:
            stack.append(j)

    height = [1] * (N + 1)

    for i in reversed(order):
        for j in children[i]:
            if height[j] + 1 > height[i]:
                height[i] = height[j] + 1

    pq = [(-height[u], u) for u in roots]
    heapq.heapify(pq)

    total_courses = 0
    for i in range(M):
        if not pq:
            break

        taken = []
        for i in range(min(K, len(pq))):
            _, j = heapq.heappop(pq)
            taken.append(j)
            total_courses +=1
        
        for k in taken:
            for h in children[k]:
                heapq.heappush(pq, (-height[h], h))

    return total_courses

def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()