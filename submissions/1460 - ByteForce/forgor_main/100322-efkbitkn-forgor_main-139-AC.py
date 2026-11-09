import sys
import heapq

MOD = 1_000_000


def prufer_to_edges(n, prufer):
    # Degree count
    degree = [1] * (n + 1)
    for x in prufer:
        degree[x] += 1

    heap = [i for i in range(1, n + 1) if degree[i] == 1]
    heapq.heapify(heap)

    edges = []
    for x in prufer:
        leaf = heapq.heappop(heap)
        edges.append((leaf, x))
        degree[leaf] -= 1
        degree[x] -= 1
        if degree[x] == 1:
            heapq.heappush(heap, x)

    # Last two nodes
    a = heapq.heappop(heap)
    b = heapq.heappop(heap)
    edges.append((a, b))
    return edges


def tree_to_prufer(n, adj):
    degree = [0] * (n + 1)
    for i in range(1, n + 1):
        degree[i] = len(adj[i])

    heap = [i for i in range(1, n + 1) if degree[i] == 1]
    heapq.heapify(heap)

    removed = [False] * (n + 1)
    prufer = []

    for _ in range(n - 2):
        leaf = heapq.heappop(heap)
        removed[leaf] = True
        # The leaf has exactly one remaining neighbor
        for nb in adj[leaf]:
            if not removed[nb]:
                prufer.append(nb)
                degree[nb] -= 1
                degree[leaf] -= 1
                if degree[nb] == 1:
                    heapq.heappush(heap, nb)
                break

    return prufer


def solve():
    data = sys.stdin.read().strip().split()
    if not data:
        return

    phase = data[0]
    idx = 1

    if phase == "FIRST":
        n = int(data[idx])
        idx += 1

        adj = [[] for _ in range(n + 1)]
        for _ in range(n - 1):
            u = int(data[idx])
            v = int(data[idx + 1])
            idx += 2
            adj[u].append(v)
            adj[v].append(u)

        if n == 2:
            # Prüfer sequence is empty
            print("0 0")
            return

        prufer = tree_to_prufer(n, adj)
        checksum = sum(prufer) % MOD

        # N numbers: N-2 Prüfer values + checksum + 0
        ans = prufer + [checksum, 0]
        print(" ".join(map(str, ans)))

    else:  # SECOND
        n = int(data[idx])
        idx += 1
        a = list(map(int, data[idx:idx + n]))

        if n == 2:
            print("1 2")
            return

        # Find the position containing -1
        missing_idx = -1
        for i, val in enumerate(a):
            if val == -1:
                missing_idx = i
                break

        prufer = a[:n - 2]
        checksum = a[n - 2]

        if missing_idx != -1 and missing_idx < n - 2:
            # Recover the missing Prüfer value using the checksum
            s = 0
            for i, val in enumerate(prufer):
                if i != missing_idx:
                    s += val
            recovered = (checksum - s) % MOD
            prufer[missing_idx] = recovered

        # If the missing value is at n-2 or n-1, Prüfer is already complete
        edges = prufer_to_edges(n, prufer)
        out = "\n".join(f"{u} {v}" for u, v in edges)
        sys.stdout.write(out)


if __name__ == "__main__":
    solve()
