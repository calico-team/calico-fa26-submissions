def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.
    
    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
    """
    kids = [[] for _ in range(N + 1)]
    for course in range(1, N + 1):
        kids[P[course - 1]].append(course)
    order = []
    stack = [0]
    while stack:
        u = stack.pop()
        order.append(u)
        stack.extend(kids[u])
    height = [0] * (N + 1)
    for u in reversed(order):
        h = 0
        for v in kids[u]:
            if height[v] > h:
                h = height[v]
        height[u] = h + 1
    buckets = [[] for _ in range(height[0] + 1)]
    top = 0
    for v in kids[0]:
        buckets[height[v]].append(v)
        if height[v] > top:
            top = height[v]
    taken = 0
    for _ in range(M):
        picked = []
        h = top
        while h > 0 and len(picked) < K:
            b = buckets[h]
            while b and len(picked) < K:
                picked.append(b.pop())
            if not b:
                h -= 1
        if not picked:
            break
        taken += len(picked)
        while top > 0 and not buckets[top]:
            top -= 1
        for u in picked:
            for v in kids[u]:
                buckets[height[v]].append(v)
                if height[v] > top:
                    top = height[v]
    return taken

def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()