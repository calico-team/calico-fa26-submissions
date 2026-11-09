from collections import deque, defaultdict

def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
    """
    Output a list of N integers A_1 .. A_N

    N: the number of vertices
    E: the N - 1 edges of the tree as (u, v) pairs
    """
    adj = defaultdict(list)
    for u, v in E:
        adj[u].append(v)
        adj[v].append(u)
    A = [0] * N
    dq = deque([1])
    V = {1}
    while dq:
        curr = dq.popleft()
        for nxt in adj[curr]:
            if nxt not in V:
                V.add(nxt)
                A[nxt-1] = curr
                dq.append(nxt)
    for i in range(1, N):
        A[0] ^= A[i]
    return A



def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    """
    Output the N - 1 edges of the original tree as (u, v) pairs

    N: the number of vertices
    A: the N integers A_1 .. A_N with one value replaced with -1
    """
    g = A.index(-1)
    A[g] = 0
    for i in range(N):
        if i != g:
            A[g] ^= A[i]
    E = []
    for i in range(1, N):
        E.append((i+1, A[i]))
    return E


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
