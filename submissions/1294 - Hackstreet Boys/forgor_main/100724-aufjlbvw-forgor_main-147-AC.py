def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
    """
    Output a list of N integers A_1 .. A_N

    N: the number of vertices
    E: the N - 1 edges of the tree as (u, v) pairs
    """
    MOD = 999983

    adj = [[] for _ in range(N + 1)]

    for u, v in E:
        adj[u].append(v)
        adj[v].append(u)

    parent = [0] * (N + 1)
    parent[1] = 0

    stack = [1]

    while stack:
        u = stack.pop()

        for v in adj[u]:
            if v != parent[u]:
                parent[v] = u
                stack.append(v)

    A = [0] * N

    checksum = 0

    for i in range(2, N + 1):
        A[i - 1] = parent[i]
        checksum += parent[i]

    A[0] = checksum % MOD

    return A


def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    """
    Output the N - 1 edges of the original tree as (u, v) pairs

    N: the number of vertices
    A: the N integers A_1 .. A_N with one value replaced with -1
    """
    MOD = 999983

    missing = A.index(-1)

    if missing == 0:
        parent = A[1:]
    else:
        checksum = A[0]

        for i in range(1, N):
            if i != missing:
                checksum -= A[i]

        missing_parent = checksum % MOD

        parent = A[1:]
        parent[missing - 1] = missing_parent

    edges = []

    for i in range(2, N + 1):
        edges.append((i, parent[i - 2]))

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