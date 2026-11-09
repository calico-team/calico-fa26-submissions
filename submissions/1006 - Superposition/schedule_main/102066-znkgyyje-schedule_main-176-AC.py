def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.
    
    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
    """
    # YOUR CODE HERE
    from heapq import heappush, heappop

    children = []
    for i in range(N + 1):
        children.append([])
    for i in range(1, N + 1):
        p = P[i - 1]
        if p != 0:
            children[p].append(i)

    
    height = []
    for i in range(N + 1):
        height.append(1)

    num_children = []
    for i in range(N + 1):
        num_children.append(len(children[i]))

    queue = []
    for i in range(1, N + 1):
        if num_children[i] == 0:
            queue.append(i)

    head = 0
    while head < len(queue):
        u = queue[head]
        head += 1
        p = P[u - 1]
        if p != 0:
            if height[u] + 1 > height[p]:
                height[p] = height[u] + 1
            num_children[p] -= 1
            if num_children[p] == 0:
                queue.append(p)

    
    heap = []
    for i in range(1, N + 1):
        if P[i - 1] == 0:
            heappush(heap, (-height[i], i))

    taken = 0
    for _ in range(M):
        if len(heap) == 0:
            break
        newly_available = []
        count = 0
        while count < K and len(heap) > 0:
            neg_h, u = heappop(heap)
            taken += 1
            count += 1
            for v in children[u]:
                newly_available.append(v)
        for v in newly_available:
            heappush(heap, (-height[v], v))

    return taken

def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()