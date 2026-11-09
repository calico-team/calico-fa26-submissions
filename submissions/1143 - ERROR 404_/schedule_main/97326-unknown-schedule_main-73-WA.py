import sys
import heapq

def solve() -> None:
    data = sys.stdin.buffer.read().split()
    if not data:
        return
    it = iter(data)
    t = int(next(it))
    out = []

    for _ in range(t):
        n = int(next(it))
        m = int(next(it))
        k = int(next(it))

        children = [[] for _ in range(n + 1)]
        roots = []

        # Pi is 1-based, 0 = no prerequisite
        for v in range(1, n + 1):
            p = int(next(it))
            if p == 0:
                roots.append(v)
            else:
                children[p].append(v)

        # height[v] = longest chain starting at v, leaf = 0
        # parent appears before child in `order`, so reversed
        # order processes children before parents.
        height = [0] * (n + 1)
        order = []
        stack = roots[:]
        while stack:
            v = stack.pop()
            order.append(v)
            stack.extend(children[v])

        for v in reversed(order):
            best = -1
            for c in children[v]:
                if height[c] > best:
                    best = height[c]
            height[v] = best + 1 if best >= 0 else 0

        # Hu's greedy, truncated after M semesters
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

        out.append(str(taken))

    sys.stdout.write("\n".join(out))

if __name__ == "__main__":
    solve()