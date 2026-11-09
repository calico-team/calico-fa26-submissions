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

    children = [[] for _ in range(N+1)]
    roots = []
    
    for i in range(1, N+1):
        p = P[i - 1]
        if p == 0: roots.append(i)
        else: children[p].append(i)

    order = list(roots)
    idx = 0

    while idx < len(order):
        v = order[idx]
        idx+=1
        order.extend(children[v])

    h = [1] * (N+1)
    for v in reversed(order):
        for c in children[v]:
            if h[c] + 1 > h[v]:
                h[v] = h[c] + 1

    maxh = max(h[1:]) if N > 0 else 0
    buckets = [[] for _ in range(maxh+2)]
    size = 0
    cur = 0

    for r in roots:
        buckets[h[r]].append(r)
        size += 1
        if h[r] > cur: cur = h[r]

    taken = 0
    for i in range(M):
        if size == 0: break

        chosen = []

        while len(chosen) < K and size > 0:
            while cur > 0 and not buckets[cur]:
                cur -= 1

            b = buckets[cur]

            while b and len(chosen) < K:
                chosen.append(b.pop())
                size -= 1

        taken += len(chosen)
        
        for v in chosen:
            for c in children[v]:
                buckets[h[c]].append(c)
                size += 1
                if h[c] > cur:
                    cur = h[c]
    return taken

def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))
    
if __name__ == '__main__':
    main()