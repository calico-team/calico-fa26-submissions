def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
    adj = [[] for _ in range(N + 1)]
    for u, v in E:
        adj[u].append(v)
        adj[v].append(u)

    p = [0] * (N + 1)
    st = [1]
    while st:
        u = st.pop()
        for v in adj[u]:
            if v != p[u]:
                p[v] = u
                st.append(v)

    x = 0
    for i in range(2, N + 1):
        x ^= p[i]
    p[1] = x

    return p[1:]


def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    idx = A.index(-1)
    x = 0
    for i in range(N):
        if i != idx:
            x ^= A[i]
    A[idx] = x

    ans = []
    for i in range(1, N):
        ans.append((i + 1, A[i]))
    return ans


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