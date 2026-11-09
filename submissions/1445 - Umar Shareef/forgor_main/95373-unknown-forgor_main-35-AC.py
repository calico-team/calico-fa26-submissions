import heapq


# A tree is fully described by its Prufer sequence: repeatedly remove the
# smallest leaf and write down its only neighbour; this gives n - 2 labels.
# In phase 1 we output the Prufer sequence plus two checksums (all values
# stay below n, well inside the allowed limit). In phase 2 exactly one
# value is replaced by -1, but we can see *where* the hole is, so one
# checksum modulo n is enough to recover a missing Prufer entry: it is the
# unique value in [0, n) that makes the sum match again.

def prufer_encode(n, adj):
    deg = [len(adj[v]) for v in range(n)]
    removed = [False] * n
    leaves = [v for v in range(n) if deg[v] == 1]
    heapq.heapify(leaves)
    seq = []
    for _ in range(n - 2):
        leaf = heapq.heappop(leaves)
        removed[leaf] = True
        nxt = None
        for u in adj[leaf]:
            if not removed[u]:
                nxt = u
                break
        seq.append(nxt)
        deg[nxt] -= 1
        if deg[nxt] == 1:
            heapq.heappush(leaves, nxt)
    return seq


def prufer_decode(n, seq):
    deg = [1] * n
    for x in seq:
        deg[x] += 1
    leaves = [v for v in range(n) if deg[v] == 1]
    heapq.heapify(leaves)
    edges = []
    for x in seq:
        leaf = heapq.heappop(leaves)
        edges.append((leaf, x))
        deg[leaf] -= 1
        deg[x] -= 1
        if deg[x] == 1:
            heapq.heappush(leaves, x)
    a = heapq.heappop(leaves)
    b = heapq.heappop(leaves)
    edges.append((a, b))
    return edges


def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
    # vertices arrive numbered 1..N; work with 0..N-1 inside
    adj = [[] for _ in range(N)]
    for u, v in E:
        u -= 1
        v -= 1
        adj[u].append(v)
        adj[v].append(u)
    if N == 1:
        return [0]
    seq = prufer_encode(N, adj)
    s1 = sum(seq) % N
    s2 = sum((i + 1) * x for i, x in enumerate(seq)) % N
    return seq + [s1, s2]


def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    if N == 1:
        return []
    seq = A[:N - 2]
    if -1 in seq:
        i = seq.index(-1)
        known = sum(x for x in seq if x != -1)
        seq[i] = (A[N - 2] - known) % N
    edges = prufer_decode(N, seq)
    return [(u + 1, v + 1) for u, v in edges]


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
