import heapq

def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.

    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes
    
    """
    children = [[] for _ in range(N + 1)]
    roots = []
    for i in range(1, N + 1):
        p = P[i - 1]
        if p == 0:
            roots.append(i)
        else:
            children[p].append(i)

    # BFS order, phir reverse mein height nikalo (subtree ki sabse lambi chain)
    order = list(roots)
    for u in order:
        order.extend(children[u])
    height = [1] * (N + 1)
    for u in reversed(order):
        for v in children[u]:
            if height[v] + 1 > height[u]:
                height[u] = height[v] + 1

    heap = [(-height[r], r) for r in roots]
    heapq.heapify(heap)

    taken = 0
    for _ in range(M):
        if not heap:
            break
        batch = []
        while heap and len(batch) < K:
            batch.append(heapq.heappop(heap)[1])
        taken += len(batch)
        # children agle semester se available honge
        for u in batch:
            for v in children[u]:
                heapq.heappush(heap, (-height[v], v))
    return taken

def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()