def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
    """
    Output a list of N integers A_1 .. A_N

    N: the number of vertices
    E: the N - 1 edges of the tree as (u, v) pairs
    """
    # YOUR CODE HERE

    graph = []
    for i in range(N + 1):
        graph.append([])

    for u, v in E:
        graph[u].append(v)
        graph[v].append(u)

    parent = [0] * (N + 1)
    stack = [1]

    while stack:
        node = stack.pop()

        for neighbor in graph[node]:
            if neighbor != parent[node]:
                parent[neighbor] = node
                stack.append(neighbor)

    A = parent[2:]
    checksum = sum(A) % 1000001
    A.append(checksum)

    return A


def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    """
    Output the N - 1 edges of the original tree as (u, v) pairs

    N: the number of vertices
    A: the N integers A_1 .. A_N with one value replaced with -1
    """
    # YOUR CODE HERE
    A = A.copy()
    missing = A.index(-1)

    if missing == N - 1:
        A[missing] = sum(A[:-1]) % 1000001
    else:
        known_sum = 0

        for i in range(N - 1):
            if i != missing:
                known_sum += A[i]

        A[missing] = (A[-1] - known_sum) % 1000001

    edges = []
    for node in range(2, N + 1):
        edges.append((node, A[node - 2]))

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
