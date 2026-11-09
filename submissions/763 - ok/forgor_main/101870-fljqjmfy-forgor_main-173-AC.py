
import sys
import heapq


def solve():
    input = sys.stdin.readline

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

        
        leaves = []

        for i in range(1, n + 1):
            if degree[i] == 1:
                heapq.heappush(leaves, i)

        prufer = []

        for _ in range(n - 2):
            leaf = heapq.heappop(leaves)

            # Find its remaining neighbor
            for v in adj[leaf]:
                if degree[v] > 0:
                    neighbor = v
                    break

            prufer.append(neighbor)

            degree[leaf] = 0
            degree[neighbor] -= 1

            if degree[neighbor] == 1:
                heapq.heappush(leaves, neighbor)

        
        checksum = 0
        for x in prufer:
            checksum ^= x

        
        ans = prufer + [checksum, 0]

        print(*ans)

    elif phase == "SECOND":
        a = list(map(int, input().split()))

        k = n - 2

        # Recover a missing Prüfer sequence element
        if -1 in a[:k]:
            missing = a.index(-1)

            value = a[k]

            for i in range(k):
                if i != missing:
                    value ^= a[i]

            a[missing] = value

        prufer = a[:k]

        # Reconstruct the tree from the Prüfer sequence
        degree = [1] * (n + 1)

        for x in prufer:
            degree[x] += 1

        leaves = []

        for i in range(1, n + 1):
            if degree[i] == 1:
                heapq.heappush(leaves, i)

        result = []

        for x in prufer:
            leaf = heapq.heappop(leaves)

            result.append((leaf, x))

            degree[leaf] -= 1
            degree[x] -= 1

            if degree[x] == 1:
                heapq.heappush(leaves, x)

        
        u = heapq.heappop(leaves)
        v = heapq.heappop(leaves)

        result.append((u, v))

        for u, v in result:
            print(u, v)


if __name__ == "__main__":
    solve()
