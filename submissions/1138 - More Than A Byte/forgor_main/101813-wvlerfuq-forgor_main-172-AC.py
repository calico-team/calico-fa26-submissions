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

    parent = [0] * (N + 1)
    stack = [1]
    checksum = 0

    while stack:
        current = stack.pop()

        for neighbor in adj[current]:
            if neighbor == parent[current]:
                continue

            parent[neighbor] = current
            checksum ^= current
            stack.append(neighbor)

    return [checksum] + parent[2:]


def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    """
    Output the N - 1 edges of the original tree as (u, v) pairs

    N: the number of vertices
    A: the N integers A_1 .. A_N with one value replaced with -1
    """
    missing = A.index(-1)

    if missing != 0:
        recovered = 0

        for value in A:
            if value != -1:
                recovered ^= value

        A[missing] = recovered

    edges = []

    for i in range(1, N):
        edges.append((i + 1, A[i]))

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
