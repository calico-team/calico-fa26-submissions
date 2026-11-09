import heapq

def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.
    
    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
    """
    children = [[] for _ in range(N)]
    roots = []

    for i in range(N):
        parent = P[i] - 1

        if P[i] == 0:
            roots.append(i)
        else:
            children[parent].append(i)

    order = []
    stack = roots[:]

    while stack:
        node = stack.pop()
        order.append(node)

        for child in children[node]:
            stack.append(child)

    height = [1]*N

    for node in reversed(order):
        for child in children[node]:
            height[node] = max(height[node], height[child] + 1) 


    available = []

    for node in roots:
        heapq.heappush(available, (-height[node], node))

    completed = 0

    for semester in range(M):
        current =[]
        for _ in range(K):
            if not available:
                break

            _, node = heapq.heappop(available)
            current.append(node)
            completed += 1

        for node in current:
            for child in children[node]:
                heapq.heappush(available, (-height[child], child))

    return completed

def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()