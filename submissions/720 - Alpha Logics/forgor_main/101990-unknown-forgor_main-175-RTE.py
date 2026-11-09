def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
    """
    Output a list of N integers A_1 .. A_N

    N: the number of vertices
    E: the N - 1 edges of the tree as (u, v) pairs
    """
    adject = [[] for _ in range(N + 1)]
    for u, v in E:
        adject[u].append(v)
        adject[v].append(u)

    parameter = [0] * (N + 1)
    seenlist = [False] * (N + 1)
    seenlist[1] = True
    queue = deque([1])
    while queue:
        u = queue.popleft()
        for w in adject[u]:
            if not seenlist[w]:
                seenlist[w] = True
                parameter[w] = u
                queue.append(w)

    check = 0
    for v in range(2, N + 1):
        check ^= parameter[v]

    return [check] + parameter[2:]


def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    """
    Output the N - 1 edges of the original tree as (u, v) pairs

    N: the number of vertices
    A: the N integers A_1 .. A_N with one value replaced with -1
    """
    parameter = A[:]
    missing = parameter.index(-1)

    if missing != 0:
        value = parameter[0]
        for i in range(1, N):
            if i != missing:
                value ^= parameter[i]
        parameter[missing] = value

    return [(i + 1, parameter[i]) for i in range(1, N)]
    


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
