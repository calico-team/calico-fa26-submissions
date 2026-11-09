import sys, heapq


def main():
    data = sys.stdin.read().split()
    pos = 0
    t = int(data[pos])
    pos += 1
    out = []
    for _ in range(t):
        n, m, k = int(data[pos]), int(data[pos + 1]), int(data[pos + 2])
        pos += 3
        P = [int(x) for x in data[pos : pos + n]]
        pos += n

        children = [[] for _ in range(n + 1)]
        roots = []
        for i in range(1, n + 1):
            p = P[i - 1]
            if p == 0:
                roots.append(i)
            else:
                children[p].append(i)

        order = list(roots)
        for u in order:
            order.extend(children[u])

        h = [0] * (n + 1)
        for u in reversed(order):
            best = 0
            for c in children[u]:
                if h[c] > best:
                    best = h[c]
            h[u] = best + 1

        heap = [(-h[r], r) for r in roots]
        heapq.heapify(heap)
        taken = 0
        for _ in range(m):
            if not heap:
                break
            chosen = []
            while heap and len(chosen) < k:
                chosen.append(heapq.heappop(heap)[1])
            taken += len(chosen)
            for u in chosen:
                for c in children[u]:
                    heapq.heappush(heap, (-h[c], c))
        out.append(str(taken))
    print("\n".join(out))


main()
