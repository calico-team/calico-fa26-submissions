import sys
input = sys.stdin.readline
sys.setrecursionlimit(1000000)

def find(depth, total, taken, pool):
    if depth > sm:
        return total
    for u in taken:
        pool = pool + graph.get(u, [])

    if not pool:
        return total
    pool.sort(key=lambda x: -height[x])
    chosen = pool[:mx]
    rest = pool[mx:]
    return find(depth + 1, total + len(chosen), chosen, rest)

for _ in range(int(input())):
    cl, sm, mx = map(int, input().split())
    preq = list(map(int, input().split()))

    graph = {}
    for idx, itm in enumerate(preq):
        graph.setdefault(itm, []).append(idx + 1)
    order = [0]
    for u in order:
        order.extend(graph.get(u, []))
    height = [0] * (cl + 1)
    for u in reversed(order):
        if u:
            height[u] = 1 + max((height[c] for c in graph.get(u, [])), default=0)