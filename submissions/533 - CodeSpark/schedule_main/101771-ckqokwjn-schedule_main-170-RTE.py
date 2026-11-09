import sys, heapq

def main():
    data = sys.stdin.read().split()
    p = 0
    t = int(data[p]); p += 1
    out = []
    for _ in range(t):
        n, m, k = int(data[p]), int(data[p+1]), int(data[p+2]); p += 3
        par = [0] + [int(x) for x in data[p:p+n]]; p += n

        ch = [[] for _ in range(n + 1)]
        roots = []
        for v in range(1, n + 1):
            if par[v] == 0:
                roots.append(v)
            else:
                ch[par[v]].append(v)

        # BFS order from roots, then compute heights bottom-up
        order = roots[:]
        for v in order:
            order.extend(ch[v])
        height = [0] * (n + 1)
        for v in reversed(order):
            pv = par[v]
            if pv and height[v] + 1 > height[pv]:
                height[pv] = height[v] + 1

        heap = [(-height[v], v) for v in roots]
        heapq.heapify(heap)
        total = 0
        for _ in range(m):
            if not heap:
                break
            taken = []
            for _ in range(min(k, len(heap))):
                taken.append(heapq.heappop(heap)[1])
            total += len(taken)
            for v in taken:
                for c in ch[v]:
                    heapq.heappush(heap, (-height[c], c))
        out.append(total)
    print("\n".join(map(str, out)))

main()