
import heapq


def solve_phase1(N, E):
    adj = [[] for _ in range(N)]
    deg = [0] * N

    for u, v in E:
        u -= 1
        v -= 1
        adj[u].append(v)
        adj[v].append(u)
        deg[u] += 1
        deg[v] += 1

    leaves = [i for i in range(N) if deg[i] == 1]
    heapq.heapify(leaves)

    ptr = [0] * N
    code = []

    for _ in range(N - 2):
        u = heapq.heappop(leaves)

        while deg[adj[u][ptr[u]]] == 0:
            ptr[u] += 1

        v = adj[u][ptr[u]]
        code.append(v + 1)

        deg[u] = 0
        deg[v] -= 1

        if deg[v] == 1:
            heapq.heappush(leaves, v)

    code.append(sum(code) % 200003)
    code.append(0)

    return code


def solve_phase2(N, A):
    missing = A.index(-1)
    code = A[:N - 2]

    if missing < N - 2:
        total = sum(x for x in code if x != -1)
        code[missing] = (A[N - 2] - total) % 200003

    deg = [1] * N

    for x in code:
        deg[x - 1] += 1

    leaves = [i for i in range(N) if deg[i] == 1]
    heapq.heapify(leaves)

    edges = []

    for x in code:
        u = heapq.heappop(leaves)
        v = x - 1

        edges.append((u + 1, v + 1))

        deg[u] -= 1
        deg[v] -= 1

        if deg[v] == 1:
            heapq.heappush(leaves, v)

    u = heapq.heappop(leaves)
    v = heapq.heappop(leaves)
    edges.append((u + 1, v + 1))

    return edges


def main():
    phase = input()
    N = int(input())

    if phase == 'FIRST':
        E = [tuple(map(int, input().split())) for _ in range(N - 1)]
        print(*solve_phase1(N, E))
    else:
        A = list(map(int, input().split()))
        for u, v in solve_phase2(N, A):
            print(u, v)


if __name__ == '__main__':
    main()
