def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
    """
    Output a list of N integers A_1 .. A_N

    N: the number of vertices
    E: the N - 1 edges of the tree as (u, v) pairs
    """
    # YOUR CODE HERE
    adj = [set() for _ in range(N+1)]
    for u, v in E:
        adj[u].add(v)
        adj[v].add(u)
    parent = [-1]*(N+1)
    parent[1] = 0
    visited = [False]*(N+1)
    visited[1]=True
    stack = [1]
    while stack:
        u = stack.pop()
        for v in adj[u]:
            if not visited[v]:
                visited[v]=True
                parent[v] = u
                stack.append(v)
    A = [parent[i] for i in range(2,N+1)]
    parity=0
    for x in A:
        parity ^=x
    A.append(parity)
    return A


def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    """
    Output the N - 1 edges of the original tree as (u, v) pairs

    N: the number of vertices
    A: the N integers A_1 .. A_N with one value replaced with -1
    """
    for i in range(N):
        if A[i] == -1:
            missing = i
            break
    if missing != N-1:
        recovered = A[N-1]
        for i in range(N-1):
            if i != missing:
                recovered ^= A[i]
        A[missing] = recovered
    edges = []
    for i in range(2,N+1):
        edges.append((i,A[i-2]))
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
