import sys
import heapq

sys.setrecursionlimit(100000)


def solve():
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return

    it = iter(data)
    t = next(it)
    out = []

    for _ in range(t):
        n = next(it)
        m = next(it)
        k = next(it)

        p = [0] * (n + 1)
        children = [[] for _ in range(n + 1)]
        roots = []

        for i in range(1, n + 1):
            pi = next(it)
            p[i] = pi
            if pi == 0:
                roots.append(i)
            else:
                children[pi].append(i)

        # 1. Height - iterative postorder to avoid recursion stack overflow
        height = [0] * (n + 1)
        order = []
        stack = roots[:]

        while stack:
            u = stack.pop()
            order.append(u)
            for v in children[u]:
                stack.append(v)

        # Reverse preorder to obtain postorder
        for u in reversed(order):
            best = 0
            for v in children[u]:
                if height[v] > best:
                    best = height[v]
            height[u] = best + 1

        # 2. Hu's greedy - select up to K available nodes with greatest height
        heap = []
        for r in roots:
            heapq.heappush(heap, (-height[r], r))

        taken = 0
        semesters = 0

        while heap and semesters < m:
            batch = []
            for _ in range(min(k, len(heap))):
                _, u = heapq.heappop(heap)
                batch.append(u)

            taken += len(batch)
            semesters += 1

            for u in batch:
                for v in children[u]:
                    heapq.heappush(heap, (-height[v], v))

        out.append(str(taken))

    sys.stdout.write("\n".join(out))


if __name__ == "__main__":
    solve()
