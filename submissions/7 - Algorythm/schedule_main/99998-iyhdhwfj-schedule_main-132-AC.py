import heapq

def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.
    
    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
    """
    children = [[] for _ in range(N + 1)]
    roots = []
    for i in range(1, N + 1):
        p = P[i - 1]
        if p == 0:
            roots.append(i)
        else:
            children[p].append(i)

    # BFS order from roots, then compute heights in reverse order
    order = list(roots)
    idx = 0
    while idx < len(order):
        u = order[idx]
        idx += 1
        order.extend(children[u])

    height = [1] * (N + 1)  # longest chain starting at this course
    for u in reversed(order):
        for c in children[u]:
            if height[c] + 1 > height[u]:
                height[u] = height[c] + 1

    heap = [(-height[r], r) for r in roots]
    heapq.heapify(heap)

    taken = 0
    for _ in range(M):
        if not heap:
            break
        chosen = []
        while heap and len(chosen) < K:
            chosen.append(heapq.heappop(heap)[1])
        taken += len(chosen)
        # children become available only in later semesters
        for u in chosen:
            for c in children[u]:
                heapq.heappush(heap, (-height[c], c))
    return taken

def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()