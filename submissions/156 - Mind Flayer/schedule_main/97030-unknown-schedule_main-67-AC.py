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

    # order: parents before children (BFS from the roots)
    order = list(roots)
    for v in order:
        order.extend(children[v])

    # height[v] = number of courses on the longest chain starting at v
    height = [1] * (N + 1)
    for v in reversed(order):
        best = 0
        for c in children[v]:
            if height[c] > best:
                best = height[c]
        height[v] = best + 1

    # greedy: each semester take the K available courses with the longest chains after them
    heap = [(-height[v], v) for v in roots]
    heapq.heapify(heap)
    taken = 0
    for _ in range(M):
        if not heap:
            break
        chosen = []
        while heap and len(chosen) < K:
            chosen.append(heapq.heappop(heap)[1])
        taken += len(chosen)
        for v in chosen:
            for c in children[v]:
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