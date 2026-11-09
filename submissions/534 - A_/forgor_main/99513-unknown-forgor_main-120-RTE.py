def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
    """
    Output a list of N integers A_1 .. A_N

    N: the number of vertices
    E: the N - 1 edges of the tree as (u, v) pairs
    """
    # YOUR CODE HERE
    adj = [set() for _ in range(N)]
    for u, v in E:
        adj[u].add(v)
        adj[v].add(u)
    parent = [-1]*N
    parent[0] = N
    stack = [0]
    while stack:
        u = stack.pop()
        for v in adj[u]:
            if v == parent[u]:
                continue
            parent[v] = u
            stack.append(v)
    x = 0
    for p in parent:
        x = x*(N+1)+p
    return[x]*N


def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    """
    Output the N - 1 edges of the original tree as (u, v) pairs

    N: the number of vertices
    A: the N integers A_1 .. A_N with one value replaced with -1
    """
    for v in A:
        if v != -1:
            x = v
            break
    parent=[0]*N
    for i in range(N-1,-1,-1):
        parent[i] = x%(N+1)
        x//=(N+1)
    edges = []
    for i in range(N):
        if i !=0:
            edges.append((i,parent[i]))
    return []


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
