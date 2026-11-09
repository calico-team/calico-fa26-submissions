
import sys
import heapq

def amnesiac():
    phase = input().strip()
    n = int(input())

    if phase == "FIRST":
        adj = [[] for _ in range(n + 1)]
        degree = [0] * (n + 1)

        for _ in range(n - 1):
            u, v = map(int, input().split())
            adj[u].append(v)
            adj[v].append(u)
            degree[u] += 1
            degree[v] += 1

        leaves = [i for i in range(1, n + 1)
                  if degree[i] == 1]
        heapq.heapify(leaves)

        code = []
        checksum = 0

        for _ in range(n - 2):
            leaf = heapq.heappop(leaves)
            degree[leaf] = 0

            for v in adj[leaf]:
                if degree[v] > 0:
                    parent = v
                    break

            code.append(parent)
            checksum ^= parent

            degree[parent] -= 1

            if degree[parent] == 1:
                heapq.heappush(leaves, parent)

        code.append(checksum)
        code.append(0)

        print(*code)

    elif phase == "SECOND":
        a = list(map(int, input().split()))

        missing = -1

        for i in range(n - 2):
            if a[i] == -1:
                missing = i
                break

        if missing != -1:
            value = a[n - 2]

            for i in range(n - 2):
                if i != missing:
                    value ^= a[i]

            a[missing] = value

        code = a[:n - 2]

        degree = [1] * (n + 1)

        for v in code:
            degree[v] += 1

        leaves = [i for i in range(1, n + 1)
                  if degree[i] == 1]
        heapq.heapify(leaves)

        output = []

        for v in code:
            leaf = heapq.heappop(leaves)

            output.append(f"{leaf} {v}")

            degree[leaf] -= 1
            degree[v] -= 1

            if degree[v] == 1:
                heapq.heappush(leaves, v)

        u = heapq.heappop(leaves)
        v = heapq.heappop(leaves)

        output.append(f"{u} {v}")

        sys.stdout.write("\n".join(output) + "\n")

if __name__ == "__main__":
    amnesiac()
