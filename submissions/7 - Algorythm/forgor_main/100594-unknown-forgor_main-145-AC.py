def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
    """
    Output a list of N integers A_1 .. A_N

    N: the number of vertices
    E: the N - 1 edges of the tree as (u, v) pairs
    """
    adj = [[] for _ in range(N + 1)]
    deg = [0] * (N + 1)
    for u, v in E:
        adj[u].append(v)
        adj[v].append(u)
        deg[u] += 1
        deg[v] += 1

    # root the tree at N, compute parents (iterative BFS)
    par = [0] * (N + 1)
    seen = [False] * (N + 1)
    seen[N] = True
    stack = [N]
    while stack:
        x = stack.pop()
        for y in adj[x]:
            if not seen[y]:
                seen[y] = True
                par[y] = x
                stack.append(y)

    # Pruefer sequence in O(N)
    seq = []
    ptr = 1
    while deg[ptr] != 1:
        ptr += 1
    leaf = ptr
    for _ in range(N - 2):
        p = par[leaf]
        seq.append(p)
        deg[p] -= 1
        if deg[p] == 1 and p < ptr:
            leaf = p
        else:
            ptr += 1
            while deg[ptr] != 1:
                ptr += 1
            leaf = ptr

    x = 0
    for v in seq:
        x ^= v
    A = seq + [x, 0]
    return A


def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    """
    Output the N - 1 edges of the original tree as (u, v) pairs

    N: the number of vertices
    A: the N integers A_1 .. A_N with one value replaced with -1
    """
    A = A[:]
    seq = A[:N - 2]
    parity = A[N - 2]
    # recover erased sequence value if needed
    for i in range(N - 2):
        if seq[i] == -1:
            x = parity
            for j in range(N - 2):
                if j != i:
                    x ^= seq[j]
            seq[i] = x
            break

    deg = [1] * (N + 1)
    for v in seq:
        deg[v] += 1

    edges = []
    ptr = 1
    while deg[ptr] != 1:
        ptr += 1
    leaf = ptr
    for v in seq:
        edges.append((leaf, v))
        deg[v] -= 1
        if deg[v] == 1 and v < ptr:
            leaf = v
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