def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
    if N == 2:
        return [0, 0]

    adj = [[] for _ in range(N + 1)]
    deg = [0] * (N + 1)
    for u, v in E:
        adj[u].append(v)
        adj[v].append(u)
        deg[u] += 1
        deg[v] += 1

    parent = [0] * (N + 1)
    stack = [N]
    visited = [False] * (N + 1)
    visited[N] = True
    while stack:
        u = stack.pop()
        for v in adj[u]:
            if not visited[v]:
                visited[v] = True
                parent[v] = u
                stack.append(v)

    ptr = 1
    while ptr <= N and deg[ptr] != 1:
        ptr += 1

    leaf = ptr
    prufer = []
    for _ in range(N - 2):
        nxt = parent[leaf]
        prufer.append(nxt)
        deg[nxt] -= 1
        if deg[nxt] == 1 and nxt < ptr:
            leaf = nxt
        else:
            ptr += 1
            while ptr <= N and deg[ptr] != 1:
                ptr += 1
            leaf = ptr

    x = 0
    for v in prufer:
        x ^= v

    return prufer + [x, 0]


def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    if N == 2:
        return [(1, 2)]

    idx = A.index(-1)
    if idx < N - 2:
        val = A[N - 2]
        for i in range(N - 2):
            if i != idx:
                val ^= A[i]
        A[idx] = val

    prufer = A[:N - 2]
    deg = [1] * (N + 1)
    for v in prufer:
        deg[v] += 1

    ptr = 1
    while ptr <= N and deg[ptr] != 1:
        ptr += 1

    leaf = ptr
    edges = []
    for v in prufer:
        edges.append((leaf, v))
        deg[v] -= 1
        if deg[v] == 1 and v < ptr:
            leaf = v
        else:
            ptr += 1
            while ptr <= N and deg[ptr] != 1:
                ptr += 1
            leaf = ptr

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
