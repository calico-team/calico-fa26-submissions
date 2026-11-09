import sys
import heapq

def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return
    it = iter(data)
    t = next(it)
    out = []

    for _ in range(t):
        try:
            n = next(it)
        except StopIteration:
            break
        m = next(it)
        k = next(it)

        parent = [0] * (n + 1)
        children = [[] for _ in range(n + 1)]
        roots = []
        for v in range(1, n + 1):
            p = next(it)
            parent[v] = p
            if p == 0:
                roots.append(v)
            else:
                children[p].append(v)

        # height = longest path to a leaf (0 for leaf)
        # iterative postorder
        height = [0] * (n + 1)
        order = []
        stack = roots[:]
        while stack:
            v = stack.pop()
            order.append(v)
            for c in children[v]:
                stack.append(c)
        for v in reversed(order):
            best = -1
            for c in children[v]:
                if height[c] > best:
                    best = height[c]
            height[v] = best + 1 if best >= 0 else 0

        # Hu's greedy, truncated to M semesters
        heap = [(-height[v], v) for v in roots]
        heapq.heapify(heap)

        taken = 0
        sem = 0
        while sem < m and heap:
            sem += 1
            take = k if k < len(heap) else len(heap)
            for _ in range(take):
                _, v = heapq.heappop(heap)
                taken += 1
                for c in children[v]:
                    heapq.heappush(heap, (-height[c], c))
            # if heap empty, remaining semesters do nothing
        out.append(str(taken))

    sys.stdout.write("\n".join(out))

if __name__ == "__main__":
    solve()