def layout(N: int) -> tuple[int, int, int]:
    m = N + 1
    s = 1
    while s < N.bit_length() and N + m * (2 ** (s + 1) - 1) <= 10 ** 6:
        s += 1
    C = -(-N.bit_length() // s)
    return m, s, C


def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
    """
    Output a list of N integers A_1 .. A_N

    N: the number of vertices
    E: the N - 1 edges of the tree as (u, v) pairs
    """
    # YOUR CODE HERE
    m, s, C = layout(N)
    adj = [[] for _ in range(N + 1)]
    for u, v in E:
        adj[u].append(v)
        adj[v].append(u)

    parent = [0] * (N + 1)
    seen = [False] * (N + 1)
    seen[1] = True
    queue = [1]
    for u in queue:
        for v in adj[u]:
            if not seen[v]:
                seen[v] = True
                parent[v] = u
                queue.append(v)

    total = 0
    for p in parent:
        total ^= p

    mask = (1 << s) - 1
    return [parent[i] + m * ((total >> (s * ((i - 1) % C))) & mask)
            for i in range(1, N + 1)]


def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    """
    Output the N - 1 edges of the original tree as (u, v) pairs

    N: the number of vertices
    A: the N integers A_1 .. A_N with one value replaced with -1
    """
    # YOUR CODE HERE
    m, s, C = layout(N)
    missing = A.index(-1) + 1

    parent = [0] * (N + 1)
    chunks = [0] * C
    known = 0
    for i in range(1, N + 1):
        if i != missing:
            parent[i] = A[i - 1] % m
            chunks[(i - 1) % C] = A[i - 1] // m
            known ^= parent[i]

    total = 0
    for c in range(C):
        total |= chunks[c] << (s * c)
    parent[missing] = total ^ known

    return [(i, parent[i]) for i in range(2, N + 1)]


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