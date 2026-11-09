
import sys
import heapq

LIMIT = 1_000_000


def amnesiac():
    tokens = sys.stdin.buffer.read().split()
    phase = tokens[0].decode()
    n = int(tokens[1])

    if phase == "FIRST":

        graph = [[] for _ in range(n + 1)]
        degree = [0] * (n + 1)

        pos = 2

        for _ in range(n - 1):
            u = int(tokens[pos])
            v = int(tokens[pos + 1])
            pos += 2

            graph[u].append(v)
            graph[v].append(u)

            degree[u] += 1
            degree[v] += 1

        # Generate the Prüfer sequence.
        leaves = [
            i for i in range(1, n + 1)
            if degree[i] == 1
        ]
        heapq.heapify(leaves)

        prufer = []

        for _ in range(n - 2):
            leaf = heapq.heappop(leaves)

            for neighbor in graph[leaf]:
                if degree[neighbor] > 0:
                    prufer.append(neighbor)

                    degree[leaf] = 0
                    degree[neighbor] -= 1

                    if degree[neighbor] == 1:
                        heapq.heappush(leaves, neighbor)

                    break

        # Store the checksum in two integers.
        total = sum(prufer)

        remainder = total % LIMIT
        quotient = total // LIMIT

        answer = prufer + [remainder, quotient]

        print(*answer)

    else:

        arr = list(map(int, tokens[2:2 + n]))

        # Find the erased position.
        missing = arr.index(-1)

        # Recover a missing Prüfer value.
        if missing < n - 2:

            total = arr[n - 2] + LIMIT * arr[n - 1]

            known_sum = sum(
                x for x in arr[:n - 2]
                if x != -1
            )

            arr[missing] = total - known_sum

        prufer = arr[:n - 2]

        # Reconstruct the original tree.
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

        # Connect the final two remaining vertices.
        u = heapq.heappop(leaves)
        v = heapq.heappop(leaves)

        edges.append((u, v))

        for u, v in edges:
            print(u, v)


def read_your_input():
    amnesiac()


if __name__ == "__main__":
    read_your_input()
