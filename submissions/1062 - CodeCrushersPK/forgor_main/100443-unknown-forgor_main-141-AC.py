from heapq import heapify, heappop, heappush


def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
    """
    Output a list of N integers A_1 .. A_N

    N: the number of vertices
    E: the N - 1 edges of the tree as (u, v) pairs
    """
    if N == 2:
        return [0, 0]

    graph = [[] for _ in range(N + 1)]
    for u, v in E:
        graph[u].append(v)
        graph[v].append(u)
    deg = [len(graph[i]) for i in range(N + 1)]
    leaf_heap = [i for i in range(1, N + 1) if deg[i] == 1]
    heapify(leaf_heap)

    sequence = []
    
    for _ in range(N - 2):
        cur = heappop(leaf_heap)
        
        for nbr in graph[cur]:
        
            if deg[nbr] > 0:
                sequence.append(nbr)
                deg[cur] = 0
                deg[nbr] -= 1
                if deg[nbr] == 1:
                    heappush(leaf_heap, nbr)
                break

    chk = sum(sequence) % 1_000_000
    return sequence + [chk, 0]


def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    """
    Output the N - 1 edges of the original tree as (u, v) pairs

    N: the number of vertices
    A: the N integers A_1 .. A_N with one value replaced with -1
    """
    if N == 2:
        return [(1, 2)]
    missing_pos = A.index(-1)
    sequence = A[: N - 2]
    if missing_pos < N - 2:
        checksum = A[N - 2]
        known_sum = sum(sequence) + 1
        sequence[missing_pos] = (checksum - known_sum) % 1_000_000

    degree = [1] * (N + 1)
    for node in sequence:
        degree[node] += 1

    leaves = [i for i in range(1, N + 1) if degree[i] == 1]
    heapify(leaves)

    edges = []
    for node in sequence:
        leaf = heappop(leaves)
        edges.append((leaf, node))
        degree[leaf] = 0
        degree[node] -= 1

        if degree[node] == 1:
            heappush(leaves, node)
    edges.append((leaves[0], leaves[1]))
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
