def solve_phase1(N, E):
    adj = [[] for _ in range(N + 1)]
    for u, v in E:
        adj[u].append(v)
        adj[v].append(u)

    parent = [0] * (N + 1)
    visited = [False] * (N + 1)
    visited[1] = True
    queue = [1]

    for u in queue:
        for v in adj[u]:
            if not visited[v]:
                visited[v] = True
                parent[v] = u
                queue.append(v)

    A = [0] * N
    checksum = 0
    for i in range(2, N + 1):
        A[i - 1] = parent[i]
        checksum ^= parent[i]
    A[0] = checksum

    return A


def solve_phase2(N, A):
    missing_index = -1
    for i in range(N):
        if A[i] == -1:
            missing_index = i
            break

    if missing_index > 0:
        recovered = A[0]
        for i in range(1, N):
            if i != missing_index:
                recovered ^= A[i]
        A[missing_index] = recovered

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