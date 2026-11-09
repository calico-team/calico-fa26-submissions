def phase1(N, edges):
    adj = [[] for _ in range(N + 1)]
    for a, b in edges:
        adj[a].append(b)
        adj[b].append(a)

    p = [0] * (N + 1)
    seen = [False] * (N + 1)
    stack = [1]
    seen[1] = True
    while stack:
        v = stack.pop()
        for u in adj[v]:
            if not seen[u]:
                seen[u] = True
                p[u] = v
                stack.append(u)

    A = []
    for i in range(1, N + 1):
        nxt = i % N + 1
        A.append(p[i] * (N + 1) + p[nxt])
    return A


def phase2(N, A):
    p = [0] * (N + 1)
    for i in range(N):
        if A[i] != -1:
            p[i + 1] = A[i] // (N + 1)
        else:
            p[i + 1] = A[i - 1] % (N + 1)

    edges = []
    for i in range(2, N + 1):
        edges.append((i, p[i]))
    return edges
def main():
    phase = int(input())
    N = int(input())

    if phase == 1:
        edges = []
        for _ in range(N - 1):
            a, b = map(int, input().split())
            edges.append((a, b))
        A = phase1(N, edges)
        print(*A)
    else:
        A = list(map(int, input().split()))
        for a, b in phase2(N, A):
            print(a, b)


main()