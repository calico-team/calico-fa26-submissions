MOD = 1000003
def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
    """
    Output a list of N integers A_1 .. A_N

    N: the number of vertices
    E: the N - 1 edges of the tree as (u, v) pairs
    """
    # YOUR CODE HERE
    m = 1000001 

    adj = [[] for _ in range(N + 1)]
    for u, v in E:
        adj[u].append(v)
        adj[v].append(u)

    parent = [0] * (N + 1)
    seen = [False] * (N + 1)
    seen[1] = True
    stack = [1]

    while stack:
        cur = stack.pop()
        for nxt in adj[cur]:
            if not seen[nxt]:
                seen[nxt] = True
                parent[nxt] = cur
                stack.append(nxt)

    A = parent[1:]            
    A[0] = sum(A[1:]) % m     
    return A


def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    """
    Output the N - 1 edges of the original tree as (u, v) pairs

    N: the number of vertices
    A: the N integers A_1 .. A_N with one value replaced with -1
    """
    # YOUR CODE HERE
    m = 1000001

    par = A[:]
    lost = par.index(-1)

    if lost != 0:
        others = sum(par[i] for i in range(1, N) if i != lost)
        par[lost] = (A[0] - others) % m

    return [(i + 1, par[i]) for i in range(1, N)]


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
