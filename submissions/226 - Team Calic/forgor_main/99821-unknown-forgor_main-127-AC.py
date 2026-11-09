def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
    """
    Output a list of N integers A_1 .. A_N

    N: the number of vertices
    E: the N - 1 edges of the tree as (u, v) pairs
    """
    if N == 2:
        return [0, 0]

    adj = [[] for _ in range(N + 1)]
    deg = [0] * (N + 1)
    for u, v in E:
        adj[u].append(v)
        adj[v].append(u)
        deg[u] += 1
        deg[v] += 1

    # root the tree at N
    parent = [0] * (N + 1)
    parent[N] = -1
    order = [N]
    head = 0
    while head < len(order):
        u = order[head]
        head += 1
        for v in adj[u]:
            if v != parent[u]:
                parent[v] = u
                order.append(v)

    # linear-time Prufer encoding
    P = []
    ptr = 1
    while deg[ptr] != 1:
        ptr += 1
    leaf = ptr
    for _ in range(N - 2):
        p = parent[leaf]
        P.append(p)
        deg[p] -= 1
        if deg[p] == 1 and p < ptr:
            leaf = p
        else:
            ptr += 1
            while deg[ptr] != 1:
                ptr += 1
            leaf = ptr

    x = 0
    for v in P:
        x ^= v
    return P + [x, 0]

def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    """
    Output the N - 1 edges of the original tree as (u, v) pairs

    N: the number of vertices
    A: the N integers A_1 .. A_N with one value replaced with -1
    """
    if N == 2:
        return [(1, 2)]

    P = A[:N - 2]
    chk = A[N - 2]
    # recover the missing Prufer entry
    if -1 in P:
        idx = P.index(-1)
        x = chk
        for i in range(N - 2):
            if i != idx:
                x ^= P[i]
        P[idx] = x

    deg = [1] * (N + 1)
    for p in P:
        deg[p] += 1

    edges = []
    ptr = 1
    while deg[ptr] != 1:
        ptr += 1
    leaf = ptr
    for p in P:
        edges.append((leaf, p))
        deg[p] -= 1
        if deg[p] == 1 and p < ptr:
            leaf = p
        else:
            ptr += 1
            while deg[ptr] != 1:
                ptr += 1
            leaf = ptr
    edges.append((leaf, N))
    return edges

def main():
    phase = input()
    N = int(input())
    if phase == 'FIRST':
        E = []
        for _ in range(N - 1):
            u, v = map(int, input().split())
            E.append((u, v))
        A = solve_phase1(N, E)
        print(' '.join(map(str, A)))
    else:
        A = list(map(int, input().split()))
        for u, v in solve_phase2(N, A):
            print(u, v)


if __name__ == '__main__':
    main()
