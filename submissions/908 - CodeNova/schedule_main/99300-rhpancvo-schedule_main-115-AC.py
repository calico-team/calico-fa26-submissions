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

    order = list(roots)
    for u in order:
        order.extend(children[u])

    height = [1] * (N + 1)
    for u in reversed(order):
        for c in children[u]:
            if height[c] + 1 > height[u]:
                height[u] = height[c] + 1

    maxh = max(height[1:]) if N > 0 else 1
    buckets = [[] for _ in range(maxh + 2)]
    cur = 1
    for r in roots:
        buckets[height[r]].append(r)
        if height[r] > cur:
            cur = height[r]

    taken = 0
    for _ in range(M):
        chosen = []
        h = cur
        while len(chosen) < K and h >= 1:
            b = buckets[h]
            while b and len(chosen) < K:
                chosen.append(b.pop())
            if len(chosen) < K:
                h -= 1
        if not chosen:
            break
        taken += len(chosen)
        cur = max(h, 1)

        for u in chosen:
            for c in children[u]:
                buckets[height[c]].append(c)
                if height[c] > cur:
                    cur = height[c]
        


    return taken

def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()