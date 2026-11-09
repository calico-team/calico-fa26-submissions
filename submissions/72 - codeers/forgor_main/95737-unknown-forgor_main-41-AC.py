import heapq


def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
    """
    Output a list of N integers A_1 .. A_N
    
    N: the number of vertices
    E: the N - 1 edges of the tree as (u, v) pairs
    """
    
    adj = [[] for _ in range(N + 1)]
    degree = [0] * (N + 1)

    for u, v in E:
        adj[u].append(v)
        adj[v].append(u)
        degree[u] += 1
        degree[v] += 1

    leaves = [i for i in range(1, N + 1) if degree[i] == 1]
    heapq.heapify(leaves)

    prufer = []

    for _ in range(N - 2):
        u = heapq.heappop(leaves)

        for v in adj[u]:
            if degree[v] > 0:
                break

        prufer.append(v)

        degree[u] = 0
        degree[v] -= 1

        if degree[v] == 1:
            heapq.heappush(leaves, v)

    # Calculate XOR checksum
    checksum = 0
    for x in prufer:
        checksum ^= x

    return prufer + [checksum, 0]


def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    """
    Output the N - 1 edges of the original tree as (u, v) pairs
    
    N: the number of vertices
    A: the N integers A_1 .. A_N with one value replaced with -1
    """
    missing = A.index(-1)

    # Recover a missing Prüfer sequence value
    if missing < N - 2:
        value = A[N - 2]

        for i in range(N - 2):
            if i != missing:
                value ^= A[i]

        A[missing] = value

    prufer = A[:N - 2]

    # Decode the Prüfer sequence
    degree = [1] * (N + 1)

    for x in prufer:
        degree[x] += 1

    leaves = [
        i for i in range(1, N + 1)
        if degree[i] == 1
    ]
    heapq.heapify(leaves)

    edges = []

    for x in prufer:
        u = heapq.heappop(leaves)

        edges.append((u, x))

        degree[u] -= 1
        degree[x] -= 1

        if degree[x] == 1:
            heapq.heappush(leaves, x)

    # Connect the final two vertices
    u = heapq.heappop(leaves)
    v = heapq.heappop(leaves)

    edges.append((u, v))

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
