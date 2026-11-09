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

    # BFS order from roots, then height = longest chain starting at node
    order = roots[:]
    head = 0
    while head < len(order):
        u = order[head]
        head += 1
        for v in children[u]:
            order.append(v)

    height = [1] * (N + 1)
    for u in reversed(order):
        for v in children[u]:
            if height[v] + 1 > height[u]:
                height[u] = height[v] + 1

    buckets = [[] for _ in range(N + 2)]
    ptr = 0
    for r in roots:
        buckets[height[r]].append(r)
        if height[r] > ptr:
            ptr = height[r]

    total = 0
    for _ in range(M):
        taken = []
        while len(taken) < K and ptr >= 1:
            if buckets[ptr]:
                taken.append(buckets[ptr].pop())
            else:
                ptr -= 1
        if not taken:
            break
        total += len(taken)
        # children become available only from the NEXT semester
        for u in taken:
            for v in children[u]:
                buckets[height[v]].append(v)
                if height[v] > ptr:
                    ptr = height[v]
    return total

def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()