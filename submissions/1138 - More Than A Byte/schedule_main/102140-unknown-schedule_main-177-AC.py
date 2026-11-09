def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.
    
    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
    """
    children = [[] for _ in range(N + 1)]
    for i in range(1, N + 1):
        children[P[i - 1]].append(i)

    depth = [0] * (N + 1)
    queue = [c for c in children[0]]
    for c in queue:
        depth[c] = 1
    head = 0
    while head < len(queue):
        u = queue[head]; head += 1
        for c in children[u]:
            depth[c] = depth[u] + 1
            queue.append(c)

    depthCount = [0] * (M + 2)
    for i in range(1, N + 1):
        d = depth[i]
        if d <= M:
            depthCount[d] += 1

    pool = 0
    taken = 0
    for s in range(1, M + 1):
        pool += depthCount[s]
        take = K if K < pool else pool
        taken += take
        pool -= take
        if taken == N:
            break

    return taken


def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()