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

    par = [0] * (N + 1)
    seen = [False] * (N + 1)
    seen[N] = True
    stack = [N]
    while stack:
        u = stack.pop()
        for w in adj[u]:
            if not seen[w]:
                seen[w] = True
                par[w] = u
                stack.append(w)

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

    A = seq + [0] * (N - len(seq) - 1)
    x = 0
    for a in A:
        x ^= a
    A.append(x)
    return A


def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    """
    Output the N - 1 edges of the original tree as (u, v) pairs

    N: the number of vertices
    A: the N integers A_1 .. A_N with one value replaced with -1
    """
    idx = A.index(-1)
    x = 0
    for i, a in enumerate(A):
        if i != idx:
            x ^= a
    A[idx] = x

    seq = A[:N - 2]

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
