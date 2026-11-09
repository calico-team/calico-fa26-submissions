
def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
    """
    Output a list of N integers A_1 .. A_N

    N: the number of vertices
    E: the N - 1 edges of the tree as (u, v) pairs
    """
    adj = [[] for _ in range(N + 1)]
    for a, b in E:
        adj[a].append(b)
        adj[b].append(a)

    p = [-1] * (N + 1)
    stack = [1]

    while stack:
        u = stack.pop()
        for v in adj[u]:
            if v == p[u]:
                continue
            p[v] = u
            stack.append(v)

    out = [0] * N
    x = 0

    for i in range(2, N + 1):
        out[i - 1] = p[i]
        x ^= p[i]

    out[0] = x
    return out


def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    """
    Output the N - 1 edges of the original tree as (u, v) pairs

    N: the number of vertices
    A: the N integers A_1 .. A_N with one value replaced with -1
    """
    # YOUR CODE HERE
    pos = -1
    for i in range(N):
        if A[i] == -1:
            pos = i
            break

    if pos != 0:
        x = A[0]
        for i in range(1, N):
            if i == pos:
                continue
            x ^= A[i]
        A[pos] = x

    res = []
    for i in range(1, N):
        res.append((i + 1, A[i]))

    return res


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
