def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.
    
    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
    """
    # YOUR CODE HERE
    import heapq

    childrn = [[] for _ in range(N + 1)]
    has_preq = [False] * (N + 1)

    for i in range(1, N + 1):
        p = P[i - 1]
        if p != 0:
            childrn[p].append(i)
            has_preq[i] = True

    order = [i for i in range(1, N + 1) if not has_preq[i]]
    pos = 0
    while pos < len(order):
        u = order[pos]
        pos += 1
        for v in childrn[u]:
            order.append(v)

    height = [1] * (N + 1)
    for u in reversed(order):
        p = P[u - 1]
        if p != 0 and height[u] + 1 > height[p]:
            height[p] = height[u] + 1

    heap = []
    for i in range(1, N + 1):
        if not has_preq[i]:
            heapq.heappush(heap, (-height[i], i))

    total = 0
    for _ in range(M):
        if not heap:
            break

        taken = []
        while heap and len(taken) < K:
            taken.append(heapq.heappop(heap)[1])

        total += len(taken)

        for u in taken:
            for v in childrn[u]:
                heapq.heappush(heap, (-height[v], v))

    return total


def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()