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
    children = {}
    heap = []
    for i, p in enumerate(pre, 1):
        if p == 0:
            heap.append(Node(i))
            continue
        if p in children:
            children[p].children.append(Node(i))
            continue
        node = Node(p)
        node.children.append(Node(i))
        children[p] = node
    taken = 0
    for _ in range(m):
        print(f"{heap}\n")
        if not heap:
            break
        if len(heap) <= k:
            nheap = []
            taken += len(heap)
            for c in heap:
                if c.idx not in children:
                    continue
                for nc in children[c.idx].children:
                    nheap.append(nc)
            heapq.heapify(nheap)
            heap = nheap
            continue
        taken += k
        for _ in range(k):
            c = heapq.heappop(heap)
            if c.idx not in children:
                continue
            for nc in children[c.idx].children:
                heapq.heappush(heap, nc)
    print(f"{taken}\n")
