import sys
import heapq

def solve():
    data = iter(map(int, sys.stdin.buffer.read().split()))
    t = next(data)
    results = []

    for _ in range(t):
        n = next(data)
        m = next(data)
        k = next(data)

        p = [next(data) for _ in range(n)]

        children = [[] for _ in range(n)]
        roots = []

        for i in range(n):
            if p[i] == 0:
                roots.append(i)
            else:
                children[p[i] - 1].append(i)

        order = []
        stack = roots[:]

        while stack:
            v = stack.pop()
            order.append(v)
            stack.extend(children[v])

        height = [1] * n

        for v in reversed(order):
            for c in children[v]:
                height[v] = max(height[v], height[c] + 1)

        pq = [(-height[v], v) for v in roots]
        heapq.heapify(pq)

        total = 0

        for _ in range(m):
            batch = []

            for _ in range(k):
                if not pq:
                    break
                _, v = heapq.heappop(pq)
                batch.append(v)

            total += len(batch)

            for v in batch:
                for c in children[v]:
                    heapq.heappush(pq, (-height[c], c))

            if not pq:
                break

        results.append(str(total))

    sys.stdout.write("\n".join(results))


if __name__ == "__main__":
    solve()
