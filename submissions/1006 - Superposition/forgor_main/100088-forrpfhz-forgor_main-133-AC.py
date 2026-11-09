from collections import deque

def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
    """
    Output a list of N integers A_1 .. A_N

    N: the number of vertices
    E: the N - 1 edges of the tree as (u, v) pairs
    """
    adj = [[] for _ in range(N + 1)]
    for u, v in E:
        adj[u].append(v)
        adj[v].append(u)

    par = [0] * (N + 1)
    vis = [False] * (N + 1)
    vis[1] = True
    q = deque([1])

    while q:
        u = q.popleft()
        for v in adj[u]:
            if not vis[v]:
                vis[v] = True
                par[v] = u
                q.append(v)

    res = [0] * N
    xor_val = 0
    for i in range(2, N + 1):
        res[i - 1] = par[i]
        xor_val ^= par[i]

    res[0] = xor_val
    return res


def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    """
    Output the N - 1 edges of the original tree as (u, v) pairs

    N: the number of vertices
    A: the N integers A_1 .. A_N with one value replaced with -1
    """
    missing_idx = -1
    xor_val = 0

    for i in range(N):
        if A[i] == -1:
            missing_idx = i
        else:
            xor_val ^= A[i]

    if missing_idx > 0:
        A[missing_idx] = xor_val

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
