import sys
import heapq

MOD = 1_000_000


def solve_phase1(N, E):
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
        leaf = heapq.heappop(leaves)

        for neighbor in adj[leaf]:
            if degree[neighbor] > 0:
                break

        prufer.append(neighbor)

        degree[leaf] = 0
        degree[neighbor] -= 1

        if degree[neighbor] == 1:
            heapq.heappush(leaves, neighbor)

    checksum = sum(prufer) % MOD

    return prufer + [checksum, checksum]


def solve_phase2(N, A):
    missing = A.index(-1)
    prufer = A[:N - 2]

    if missing < N - 2:
        known_sum = sum(x for x in prufer if x != -1)
        prufer[missing] = (A[N - 2] - known_sum) % MOD

    degree = [1] * (N + 1)

    for vertex in prufer:
        degree[vertex] += 1

    leaves = [
        i for i in range(1, N + 1)
        if degree[i] == 1
    ]
    heapq.heapify(leaves)

    edges = []

    for vertex in prufer:
        leaf = heapq.heappop(leaves)
        edges.append((leaf, vertex))

        degree[leaf] = 0
        degree[vertex] -= 1

        if degree[vertex] == 1:
            heapq.heappush(leaves, vertex)

    remaining = [
        i for i in range(1, N + 1)
        if degree[i] == 1
    ]

    edges.append((remaining[0], remaining[1]))

    return edges


def main():
    phase = read_your_input()
    N = int(read_your_input())

    if phase == "FIRST":
        E = []

        for _ in range(N - 1):
            u, v = map(int, read_your_input().split())
            E.append((u, v))

        answer = solve_phase1(N, E)
        print(*answer)

    elif phase == "SECOND":
        A = list(map(int, read_your_input().split()))

        answer = solve_phase2(N, A)

        for u, v in answer:
            print(u, v)


def read_your_input():
    return sys.stdin.buffer.readline().decode().strip()


if __name__ == "__main__":
    main()