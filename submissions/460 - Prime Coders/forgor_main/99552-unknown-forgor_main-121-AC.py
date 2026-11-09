
import heapq


def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:

    # Step 1: Build the adjacency list
    graph = [[] for _ in range(N)]

    for u, v in E:
        u -= 1
        v -= 1

        graph[u].append(v)
        graph[v].append(u)

    # Step 2: Calculate the degree of every vertex
    degree = [len(graph[i]) for i in range(N)]

    # Step 3: Put all leaf vertices into a min heap
    leaves = []

    for i in range(N):
        if degree[i] == 1:
            heapq.heappush(leaves, i)

    # Step 4: Generate the Prüfer sequence
    prufer = []

    for _ in range(N - 2):

        leaf = heapq.heappop(leaves)

        # Find the remaining neighbor of this leaf
        for neighbor in graph[leaf]:
            if degree[neighbor] > 0:
                break

        prufer.append(neighbor + 1)

        # Remove the leaf
        degree[leaf] = 0
        degree[neighbor] -= 1

        if degree[neighbor] == 1:
            heapq.heappush(leaves, neighbor)

    # Step 5: Calculate XOR checksum
    checksum = 0

    for value in prufer:
        checksum ^= value

    # Store sequence, checksum and one extra value
    A = prufer + [checksum, 0]

    return A


def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:

    # Step 1: Find the missing value
    missing = A.index(-1)

    # Step 2: Recover a missing Prüfer sequence value
    if missing < N - 2:

        value = A[N - 2]

        for i in range(N - 2):
            if i != missing:
                value ^= A[i]

        A[missing] = value

    # Step 3: Extract the Prüfer sequence
    prufer = A[:N - 2]

    # Step 4: Calculate degrees
    degree = [1] * N

    for value in prufer:
        degree[value - 1] += 1

    # Step 5: Find all leaves
    leaves = []

    for i in range(N):
        if degree[i] == 1:
            heapq.heappush(leaves, i)

    # Step 6: Reconstruct the original tree
    edges = []

    for value in prufer:

        leaf = heapq.heappop(leaves)
        neighbor = value - 1

        edges.append((leaf + 1, neighbor + 1))

        degree[leaf] -= 1
        degree[neighbor] -= 1

        if degree[neighbor] == 1:
            heapq.heappush(leaves, neighbor)

    # Connect the last two remaining vertices
    first = heapq.heappop(leaves)
    second = heapq.heappop(leaves)

    edges.append((first + 1, second + 1))

    return edges


def main():

    phase = input().strip()
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

        edges = solve_phase2(N, A)

        for u, v in edges:
            print(u, v)


if __name__ == '__main__':
    main()
