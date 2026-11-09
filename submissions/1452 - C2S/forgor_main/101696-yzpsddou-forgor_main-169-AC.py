def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
    """
    Output a list of N integers A_1 .. A_N

    N: the number of vertices
    E: the N - 1 edges of the tree as (u, v) pairs
    """
    adj = [[] for _ in range(N + 1)]
    for u, v in E:
        adj[u].append(v)
        adj[v].append(u)

    # Tree ko vertex 1 pe root karo, har vertex ka parent nikalo
    parent = [0] * (N + 1)
    seen = [False] * (N + 1)
    seen[1] = True
    order = [1]
    for u in order:
        for v in adj[u]:
            if not seen[v]:
                seen[v] = True
                parent[v] = u
                order.append(v)

    # A_i = parent[i] (i >= 2), A_1 = XOR of sab parents
    A = [0] * N
    x = 0
    for i in range(2, N + 1):
        A[i - 1] = parent[i]
        x ^= parent[i]
    A[0] = x
    return A


def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    """
    Output the N - 1 edges of the original tree as (u, v) pairs

    N: the number of vertices
    A: the N integers A_1 .. A_N with one value replaced with -1
    """
    missing = A.index(-1)
    if missing != 0:
        # A_1 = XOR of sab parents, to missing parent nikalo
        x = A[0]
        for i in range(1, N):
            if i != missing:
                x ^= A[i]
        A[missing] = x

    # A_1 missing ho to bhi baaki sab parents mil chuke hain
    return [(i, A[i - 1]) for i in range(2, N + 1)]


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