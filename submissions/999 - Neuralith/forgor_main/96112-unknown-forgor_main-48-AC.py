
import sys
import heapq

MOD = 999983


def amnesiac():
    data = read_your_input()
    it = iter(data)

    phase = next(it)
    n = int(next(it))

    if phase == "FIRST":
        adj = [[] for _ in range(n + 1)]
        degree = [0] * (n + 1)

        for _ in range(n - 1):
            u = int(next(it))
            v = int(next(it))
            adj[u].append(v)
            adj[v].append(u)
            degree[u] += 1
            degree[v] += 1

        # Generate Prüfer sequence
        leaves = [i for i in range(1, n + 1)
                  if degree[i] == 1]
        heapq.heapify(leaves)

        prufer = []

        for _ in range(n - 2):
            leaf = heapq.heappop(leaves)

            for v in adj[leaf]:
                if degree[v] > 0:
                    neighbor = v
                    break

            prufer.append(neighbor)

            degree[leaf] = 0
            degree[neighbor] -= 1

            if degree[neighbor] == 1:
                heapq.heappush(leaves, neighbor)

        # Two checksums provide erasure recovery
        checksum1 = sum(prufer) % MOD

        checksum2 = sum(
            (i + 1) * x
            for i, x in enumerate(prufer)
        ) % MOD

        result = prufer + [checksum1, checksum2]

        print(*result)

    else:
        a = [int(next(it)) for _ in range(n)]

        missing = a.index(-1)

        length = n - 2

        if missing < length:
            # Recover missing Prüfer element using checksum1
            known_sum = sum(
                a[i] for i in range(length)
                if i != missing
            )

            value = (a[length] - known_sum) % MOD
            a[missing] = value

        prufer = a[:length]

        # Reconstruct tree from Prüfer sequence
        degree = [1] * (n + 1)

        for x in prufer:
            degree[x] += 1

        leaves = [
            i for i in range(1, n + 1)
            if degree[i] == 1
        ]
        heapq.heapify(leaves)

        edges = []

        for x in prufer:
            leaf = heapq.heappop(leaves)

            edges.append((leaf, x))

            degree[leaf] -= 1
            degree[x] -= 1

            if degree[x] == 1:
                heapq.heappush(leaves, x)

        u = heapq.heappop(leaves)
        v = heapq.heappop(leaves)

        edges.append((u, v))

        for u, v in edges:
            print(u, v)


def read_your_input():
    return sys.stdin.buffer.read().decode().split()


if __name__ == "__main__":
    amnesiac()
