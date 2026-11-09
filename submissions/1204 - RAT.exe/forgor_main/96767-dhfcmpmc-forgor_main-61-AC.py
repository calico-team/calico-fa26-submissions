import heapq
MOD = 1000001
def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
    
    deg = [0] * (N + 1)
    xr = [0] * (N + 1)
    for u, v in E:
        deg[u] += 1
        deg[v] += 1
        xr[u] ^= v
        xr[v] ^= u

    heap = [v for v in range(1, N + 1) if deg[v] == 1]
    heapq.heapify(heap)

    P = []
    for _ in range(N - 2):
        l = heapq.heappop(heap)
        p = xr[l]
        P.append(p)
        xr[p] ^= l
        deg[p] -= 1
        if deg[p] == 1:
            heapq.heappush(heap, p)

    return P + [sum(P) % MOD, 0]


def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    
    P = A[:N - 2]
    S = A[N - 2]
    for i in range(N - 2):
        if P[i] == -1:
            others = sum(P) + 1  # sum of P including the -1, corrected by +1
            P[i] = (S - others) % MOD
            break

    deg = [1] * (N + 1)
    for p in P:
        deg[p] += 1

    heap = [v for v in range(1, N + 1) if deg[v] == 1]
    heapq.heapify(heap)

    edges = []
    for p in P:
        l = heapq.heappop(heap)
        edges.append((l, p))
        deg[p] -= 1
        if deg[p] == 1:
            heapq.heappush(heap, p)

    a = heapq.heappop(heap)
    b = heapq.heappop(heap)
    edges.append((a, b))
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
