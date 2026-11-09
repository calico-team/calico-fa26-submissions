def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
    if N == 2: return [0, 0] # edge case handling

    adjacent = [[] for _ in range(N + 1)]
    touching = [0] * (N+1)

    for u, v in E:
        adjacent[u].append(v)
        adjacent[v].append(u)
        touching[u], touching[v] = touching[u] + 1, touching[v] + 1

    parent = [0]*(N + 1)
    parent[N] = -1
    stack = [N]

    while stack:
        x = stack.pop()
        for y in adjacent[x]:
            if y != parent[x]:
                parent[y] = x
                stack.append(y)

    sequence = []
    pointer = 1

    while touching[pointer] != 1: pointer += 1

    leaf = pointer

    for i in range(N-2):
        leaf_parent = parent[leaf]
        sequence.append(leaf_parent)
        touching[leaf_parent] -= 1

        if touching[leaf_parent] == 1 and leaf_parent < pointer: leaf = leaf_parent
        else:
            pointer += 1
            while touching[pointer] != 1: pointer += 1
            leaf = pointer

    return sequence + [sum(sequence) % (N + 1), 0]

def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    if N == 2: return [(1, 2)] # more edge case handling my beloved

    L = N-2
    sequence = A[:L]

    for i in range(L):
        if sequence[i] == -1:
            others = sum(sequence) + 1
            sequence[i] = (A[L] - others) % (N + 1)
            break

    touching = [1] * (N+1)

    for v in sequence: touching[v] += 1

    pointer = 1

    while touching[pointer] != 1:pointer += 1

    leaf = pointer
    edges = []

    for v in sequence:
        edges.append((leaf, v))
        touching[v] -= 1
        if touching[v] == 1 and v < pointer: leaf = v
        else:
            pointer += 1
            while touching[pointer] != 1: pointer += 1
            leaf = pointer

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
