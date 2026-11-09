import heapq
import sys

input = sys.stdin.readline
print = sys.stdout.write

ii = lambda: int(input())
mii = lambda: map(int, input().split())


class Node:
    def __init__(self, i) -> None:
        self.idx = i
        self.children = []

    def __lt__(self, other):
        # lt is gt
        return len(self.children) > len(other.children)

    def __repr__(self) -> str:
        return self.children.__repr__() + str(self.idx)


for _ in range(ii()):
    n, m, k = mii()
    pre = mii()
    nodes = [None] + [Node(i) for i in range(1, n + 1)]
    heap = []

    for i, p in enumerate(pre, 1):
        if p == 0:
            heap.append(nodes[i])
        else:
            nodes[p].children.append(nodes[i])

    heapq.heapify(heap)
    taken = 0
    for _ in range(m):
        if not heap:
            break
        if len(heap) <= k:
            nheap = []
            taken += len(heap)
            for c in heap:
                nheap.extend(c.children)
            heapq.heapify(nheap)
            heap = nheap
            continue
        taken += k
        new = []
        for _ in range(k):
            c = heapq.heappop(heap)
            new.extend(c.children)
        for nc in new:
            heapq.heappush(heap, nc)
    print(f"{taken}\n")
