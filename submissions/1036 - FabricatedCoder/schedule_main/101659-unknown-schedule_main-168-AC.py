import sys
import heapq

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return

    iterator = iter(input_data)
    T = int(next(iterator))

    out = []
    for _ in range(T):
        N = int(next(iterator))
        M = int(next(iterator))
        K = int(next(iterator))

        P = [int(next(iterator)) for _ in range(N)]

        children = [[] for _ in range(N + 1)]
        out_degree = [0] * (N + 1)

        for i in range(1, N + 1):
            p = P[i - 1]
            if p != 0:
                children[p].append(i)
                out_degree[p] += 1

        queue = [i for i in range(1, N + 1) if out_degree[i] == 0]
        height = [1] * (N + 1)
        size = [1] * (N + 1)

        head = 0
        while head < len(queue):
            u = queue[head]
            head += 1

            p = P[u - 1]
            if p != 0:
                height[p] = max(height[p], 1 + height[u])
                size[p] += size[u]
                out_degree[p] -= 1
                if out_degree[p] == 0:
                    queue.append(p)

        pq = []
        for i in range(1, N + 1):
            if P[i - 1] == 0:
                heapq.heappush(pq, (-height[i], -size[i], i))

        total_taken = 0

        for _ in range(M):
            if not pq:
                break

            take_count = min(K, len(pq))
            taken_nodes = []
            for _ in range(take_count):
                _, _, u = heapq.heappop(pq)
                taken_nodes.append(u)

            total_taken += len(taken_nodes)

            for u in taken_nodes:
                for v in children[u]:
                    heapq.heappush(pq, (-height[v], -size[v], v))

        out.append(str(total_taken))

    print("\n".join(out))

if __name__ == "__main__":
    solve()