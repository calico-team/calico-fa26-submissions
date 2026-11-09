from collections import deque


def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:    
    # in my very first step i'm goint o build adjacency list
    adjncy = [[] for _ in range(N + 1)]
    for u, v in E:
        adjncy[u].append(v)
        adjncy[v].append(u)

    # now i have to iterate the things to find the parents
    # this should not give the recurion, if not giveing this mught be correct
    parent = [0] * (N + 1)
    seen = [False] * (N + 1)
    seen[1] = True
    dque = deque([1])
    while dque:
        x = dque.popleft()
        for y in adjncy[x]:
            if not seen[y]:
                seen[y] = True
                parent[y] = x
                dque.append(y)

    # find the backup and parents of i
    x = 0
    for i in range(2, N + 1):
        x ^= parent[i]
    parent[1] = x
    return parent[1:]


def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    a = [0] + list(A)       # switch to 1-indexed
    k = a.index(-1, 1)      # the erased position

    if k != 1:
        # this will lost the parents part, aur main is ka kuch na kuch kr lounga
        x = a[1]
        for i in range(2, N + 1):
            if i != k:
                x ^= a[i]
        a[k] = x
    # sirf backup loose hue hai bhai lekin huanain parents abhi b intact hian

    return [(i, a[i]) for i in range(2, N + 1)]


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