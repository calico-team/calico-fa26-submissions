import sys
import heapq


def encode_tree(n, edges):
    if n == 1:
        return [0]

    adj = [[] for _ in range(n)]
    degree = [0] * n

    for u, v in edges:
        adj[u].append(v)
        adj[v].append(u)
        degree[u] += 1
        degree[v] += 1

    # Find all leaves.
    leaves = [i for i in range(n) if degree[i] == 1]
    heapq.heapify(leaves)

    prufer = []
    ptr = [0] * n

    # Generate Prüfer sequence.
    for _ in range(n - 2):
        leaf = heapq.heappop(leaves)

        # Find the remaining neighbor of this leaf.
        while degree[adj[leaf][ptr[leaf]]] == 0:
            ptr[leaf] += 1

        neighbor = adj[leaf][ptr[leaf]]

        prufer.append(neighbor)

        degree[leaf] = 0
        degree[neighbor] -= 1

        if degree[neighbor] == 1:
            heapq.heappush(leaves, neighbor)

    # Store Prüfer sequence and XOR checksum.
    answer = [0] * n
    checksum = 0

    for i, x in enumerate(prufer):
        answer[i] = x
        checksum ^= x

    answer[n - 2] = checksum
    answer[n - 1] = 0

    return answer


def decode_tree(n, a):
    if n == 1:
        return []

    k = n - 2

    # Recover an erased Prüfer sequence value.
    if -1 in a[:k]:
        missing_index = a.index(-1)

        recovered = a[k]

        for i in range(k):
            if i != missing_index:
                recovered ^= a[i]

        a[missing_index] = recovered

    prufer = a[:k]

    # Calculate vertex degrees.
    degree = [1] * n

    for x in prufer:
        degree[x] += 1

    # Find all leaves.
    leaves = [i for i in range(n) if degree[i] == 1]
    heapq.heapify(leaves)

    edges = []

    # Reconstruct the tree.
    for x in prufer:
        leaf = heapq.heappop(leaves)

        edges.append((leaf + 1, x + 1))

        degree[leaf] -= 1
        degree[x] -= 1

        if degree[x] == 1:
            heapq.heappush(leaves, x)

    # Connect the final two remaining vertices.
    u = heapq.heappop(leaves)
    v = heapq.heappop(leaves)

    edges.append((u + 1, v + 1))

    return edges


def solve():
    input = sys.stdin.readline

    phase = input().strip()
    n = int(input())

    if phase == "FIRST":
        edges = []

        for _ in range(n - 1):
            u, v = map(int, input().split())
            edges.append((u - 1, v - 1))

        answer = encode_tree(n, edges)

        print(*answer)

    else:
        a = list(map(int, input().split()))

        edges = decode_tree(n, a)

        for u, v in edges:
            print(u, v)


if __name__ == "__main__":
    solve()