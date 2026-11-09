import sys
import heapq

MOD = 1000001


def amnesiac():
    data = sys.stdin.buffer.read().split()
    if not data:
        return

    phase = data[0]

    if phase == b'FIRST':
        idx = 1
        n = int(data[idx])
        idx += 1

        adj = [[] for _ in range(n + 1)]

        for _ in range(n - 1):
            u = int(data[idx])
            v = int(data[idx + 1])
            idx += 2
            adj[u].append(v)
            adj[v].append(u)

        prufer_code = []

        if n > 2:
            degree = [0] * (n + 1)
            for node in range(1, n + 1):
                degree[node] = len(adj[node])

            leaves = [node for node in range(1, n + 1) if degree[node] == 1]
            heapq.heapify(leaves)

            for _ in range(n - 2):
                leaf = heapq.heappop(leaves)

                neighbour = -1
                for cand in adj[leaf]:
                    if degree[cand] > 0:
                        neighbour = cand
                        break

                prufer_code.append(neighbour)

                degree[leaf] -= 1
                degree[neighbour] -= 1

                if degree[neighbour] == 1:
                    heapq.heappush(leaves, neighbour)

        arr = []
        for val in prufer_code:
            arr.append(val)

        arr.append(0)

        checksum = sum(arr) % MOD
        arr.append(checksum)

        sys.stdout.write(" ".join(map(str, arr)))

    else:
        idx = 1
        n = int(data[idx])
        idx += 1

        arr = [int(data[idx + i]) for i in range(n)]

        missing_pos = -1
        for i, val in enumerate(arr):
            if val == -1:
                missing_pos = i
                break

        if missing_pos == n - 1:
            total = 0
            for i in range(n - 1):
                total += arr[i]
            arr[n - 1] = total % MOD
        else:
            checksum = arr[n - 1]
            total = 0
            for i in range(n - 1):
                if i != missing_pos:
                    total += arr[i]
            arr[missing_pos] = (checksum - total) % MOD

        prufer_code = arr[:n - 2]

        if n == 2:
            sys.stdout.write("1 2")
            return

        degree = [0] * (n + 1)
        for node in range(1, n + 1):
            degree[node] = 1

        for val in prufer_code:
            degree[val] += 1

        leaves = [node for node in range(1, n + 1) if degree[node] == 1]
        heapq.heapify(leaves)

        edges = []

        for val in prufer_code:
            leaf = heapq.heappop(leaves)
            edges.append((leaf, val))

            degree[leaf] -= 1
            degree[val] -= 1

            if degree[val] == 1:
                heapq.heappush(leaves, val)

        u = heapq.heappop(leaves)
        v = heapq.heappop(leaves)
        edges.append((u, v))

        out_lines = []
        for u, v in edges:
            out_lines.append(f"{u} {v}")

        sys.stdout.write("\n".join(out_lines))


def read_your_input():
    return sys.stdin.buffer.read()


if __name__ == "__main__":
    amnesiac()