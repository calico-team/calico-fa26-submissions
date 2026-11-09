import heapq
import sys
from collections import deque

input = sys.stdin.readline
print = sys.stdout.write

ii = lambda: int(input())
mii = lambda: map(int, input().split())


for _ in range(ii()):
    n, m, k = mii()
    pre = mii()
    heap = []

    children = [[] for _ in range(n)]
    parent = [p - 1 for p in pre]

    roots = []

    for i, p in enumerate(parent):
        if p == -1:
            roots.append(i)
        else:
            children[p].append(i)

    remaining = [len(c) for c in children]
    height = [1] * n
    q = deque(i for i in range(n) if remaining[i] == 0)

    while q:
        v = q.popleft()
        p = parent[v]
        if p == -1:
            continue
        height[p] = max(height[p], height[v] + 1)
        remaining[p] -= 1
        if remaining[p] == 0:
            q.append(p)

    heap = [(-height[v], v) for v in roots]

    heapq.heapify(heap)
    taken = 0
    for _ in range(m):
        if not heap:
            break
        if len(heap) <= k:
            nheap = []
            taken += len(heap)
            for _, v in heap:
                nheap.extend((-height[c], c) for c in children[v])
            heapq.heapify(nheap)
            heap = nheap
            continue
        taken += k
        new = []
        for _ in range(k):
            _, v = heapq.heappop(heap)
            new.extend(children[v])
        for nc in new:
            heapq.heappush(heap, (-height[nc], nc))
    print(f"{taken}\n")
