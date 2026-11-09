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

    parent = [0] * (N + 1)
    seen = [False] * (N + 1)
    seen[1] = True
    dq = deque([1])
    while dq:
        x = dq.popleft()
        for y in adj[x]:
            if not seen[y]:
                seen[y] = True
                parent[y] = x
                dq.append(y)

    A = [0] * N
    x = 0
    for i in range(2, N + 1):
        A[i - 1] = parent[i]
        x ^= parent[i]
    A[0] = x  # checksum (XOR of all parents), always < 2^18
    return A


def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    """
    Output the N - 1 edges of the original tree as (u, v) pairs

    N: the number of vertices
    A: the N integers A_1 .. A_N with one value replaced with -1
    """
    A = A[:]
    if A[0] != -1:
        # checksum is intact; if some parent is missing, rebuild it
        for i in range(1, N):
            if A[i] == -1:
                x = A[0]
                for j in range(1, N):
                    if j != i:
                        x ^= A[j]
                A[i] = x
                break
    # if A[0] was the missing one, all parents are already known
    return [(A[i - 1], i) for i in range(2, N + 1)]


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