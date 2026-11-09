def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
    graph = [[] for _ in range(N + 1)]

    for u, v in E:
        graph[u].append(v)
        graph[v].append(u)

    parent = [0] * (N + 1)
    parent[1] = -1

    stack = [1]

    while stack:
        node = stack.pop()

        for neighbor in graph[node]:
            if neighbor == parent[node]:
                continue

            parent[neighbor] = node
            stack.append(neighbor)

    A = [0] * N
    checksum = 0

    for node in range(2, N + 1):
        value = parent[node]
        A[node - 1] = value
        checksum ^= value

    A[0] = checksum

    return A


def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    missing = -1
    checksum = 0

    for i in range(N):
        if A[i] == -1:
            missing = i
        else:
            checksum ^= A[i]

    if missing > 0:
        A[missing] = checksum

    edges = []

    for node in range(2, N + 1):
        edges.append((A[node - 1], node))

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
