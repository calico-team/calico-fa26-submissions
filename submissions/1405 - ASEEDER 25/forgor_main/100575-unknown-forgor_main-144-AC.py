import sys
from heapq import heapify, heappop, heappush


def encode_tree(n, edges):
    adjacency = [[] for _ in range(n + 1)]
    degree = [0] * (n + 1)

    for u, v in edges:
        adjacency[u].append(v)
        adjacency[v].append(u)
        degree[u] += 1
        degree[v] += 1

    leaves = [vertex for vertex in range(1, n + 1) if degree[vertex] == 1]
    heapify(leaves)
    prufer = []

    for _ in range(n - 2):
        leaf = heappop(leaves)
        parent = next(
            neighbor for neighbor in adjacency[leaf] if degree[neighbor] > 0
        )
        prufer.append(parent - 1)

        degree[leaf] = 0
        degree[parent] -= 1
        if degree[parent] == 1:
            heappush(leaves, parent)

    # N - 2 values store the Prüfer sequence. One extra value stores its XOR,
    # allowing any erased sequence value to be recovered. The last is unused.
    parity = 0
    for value in prufer:
        parity ^= value
    prufer.extend((parity, 0))
    return prufer


def decode_tree(n, values):
    erased = values.index(-1)
    sequence_length = n - 2

    if erased < sequence_length:
        parity = values[sequence_length]
        remaining_xor = 0
        for i in range(sequence_length):
            if i != erased:
                remaining_xor ^= values[i]
        values[erased] = parity ^ remaining_xor

    prufer = values[:sequence_length]
    degree = [1] * (n + 1)
    for value in prufer:
        degree[value + 1] += 1

    leaves = [vertex for vertex in range(1, n + 1) if degree[vertex] == 1]
    heapify(leaves)
    edges = []

    for value in prufer:
        leaf = heappop(leaves)
        parent = value + 1
        edges.append((leaf, parent))

        degree[leaf] -= 1
        degree[parent] -= 1
        if degree[parent] == 1:
            heappush(leaves, parent)

    remaining = [vertex for vertex in range(1, n + 1) if degree[vertex] == 1]
    edges.append((remaining[0], remaining[1]))
    return edges


def solve():
    input = sys.stdin.buffer.readline
    phase = input().strip()
    n = int(input())

    if phase == b"FIRST":
        edges = [tuple(map(int, input().split())) for _ in range(n - 1)]
        values = encode_tree(n, edges)
        sys.stdout.write(" ".join(map(str, values)))
    else:
        values = list(map(int, input().split()))
        edges = decode_tree(n, values)
        sys.stdout.write("\n".join(f"{u} {v}" for u, v in edges))


if __name__ == "__main__":
    solve()
