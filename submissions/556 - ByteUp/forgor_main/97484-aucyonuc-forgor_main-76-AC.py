
import sys
import heapq

MOD = 1000003


def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
    adj = [[] for _ in range(N + 1)]
    degree = [0] * (N + 1)

    for u, v in E:
        adj[u].append(v)
        adj[v].append(u)
        degree[u] += 1
        degree[v] += 1

    leaves = [
        i for i in range(1, N + 1)
        if degree[i] == 1
    ]
    heapq.heapify(leaves)

    code = []

    for _ in range(N - 2):
        leaf = heapq.heappop(leaves)
        degree[leaf] = 0

        for v in adj[leaf]:
            if degree[v] > 0:
                code.append(v)
                degree[v] -= 1

                if degree[v] == 1:
                    heapq.heappush(leaves, v)
                break

    s1 = 0
    s2 = 0

    for i, x in enumerate(code):
        s1 = (s1 + x) % MOD
        s2 = (s2 + (i + 1) * x) % MOD

    return code + [s1, s2]


def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    k = N - 2
    missing = A.index(-1)

    if missing < k:
        if A[k] != -1:
            total = sum(
                A[i] for i in range(k)
                if i != missing
            )
            A[missing] = (A[k] - total) % MOD

        else:
            total = 0
            for i in range(k):
                if i != missing:
                    total += (i + 1) * A[i]

            remaining = (A[k + 1] - total) % MOD
            inverse = pow(missing + 1, -1, MOD)
            A[missing] = (remaining * inverse) % MOD

    code = A[:k]

    degree = [1] * (N + 1)

    for x in code:
        degree[x] += 1

    leaves = [
        i for i in range(1, N + 1)
        if degree[i] == 1
    ]
    heapq.heapify(leaves)

    edges = []

    for x in code:
        leaf = heapq.heappop(leaves)
        edges.append((leaf, x))

        degree[leaf] -= 1
        degree[x] -= 1

        if degree[x] == 1:
            heapq.heappush(leaves, x)

    u = heapq.heappop(leaves)
    v = heapq.heappop(leaves)

    edges.append((u, v))

    return edges


def main():
    input = sys.stdin.readline

    phase = input().strip()
    N = int(input())

    if phase == "FIRST":
        E = []

        for _ in range(N - 1):
            u, v = map(int, input().split())
            E.append((u, v))

        A = solve_phase1(N, E)
        print(" ".join(map(str, A)))

    elif phase == "SECOND":
        A = list(map(int, input().split()))

        edges = solve_phase2(N, A)

        for u, v in edges:
            print(u, v)


if __name__ == "__main__":
    main()
