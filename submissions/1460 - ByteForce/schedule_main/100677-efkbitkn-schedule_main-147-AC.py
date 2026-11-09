import sys
import heapq


def max_courses(n: int, m: int, k: int, parents: list[int]) -> int:
    children = [[] for _ in range(n + 1)]
    roots = []
    for course in range(1, n + 1):
        p = parents[course - 1]
        if p == 0:
            roots.append(course)
        else:
            children[p].append(course)

    # Topological order from roots downward to compute subtree heights iteratively
    order = []
    stack = list(roots)
    while stack:
        u = stack.pop()
        order.append(u)
        for v in children[u]:
            stack.append(v)

    height = [1] * (n + 1)
    for u in reversed(order):
        if children[u]:
            max_h = 0
            for v in children[u]:
                if height[v] > max_h:
                    max_h = height[v]
            height[u] = max_h + 1

    # Max-heap prioritized by (-height[u], -len(children[u]), u)
    heap = [(-height[u], -len(children[u]), u) for u in roots]
    heapq.heapify(heap)

    total_taken = 0
    for _ in range(m):
        if not heap:
            break
        take_count = k if len(heap) >= k else len(heap)
        total_taken += take_count
        unlocked = []
        for _ in range(take_count):
            _, _, u = heapq.heappop(heap)
            unlocked.extend(children[u])
        for v in unlocked:
            heapq.heappush(heap, (-height[v], -len(children[v]), v))

    return total_taken


def main():
    it = map(int, sys.stdin.buffer.read().split())
    try:
        t_cases = next(it)
    except StopIteration:
        return

    out = []
    for _ in range(t_cases):
        n = next(it)
        m = next(it)
        k = next(it)
        parents = [next(it) for _ in range(n)]
        out.append(str(max_courses(n, m, k, parents)))

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
