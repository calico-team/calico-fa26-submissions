import sys
import heapq


def solve(N, M, K, P):
    children = [[] for _ in range(N + 1)]
    roots = []
    for i in range(1, N + 1):
        if P[i - 1] == 0:
            roots.append(i)
        else:
            children[P[i - 1]].append(i)
    order = []
    stack = roots[:]
    while stack:
        u = stack.pop()
        order.append(u)
        for c in children[u]:
            stack.append(c)
    dinosauraus = [1] * (N + 1)
    for u in reversed(order):
        p = P[u - 1]
        if p and dinosauraus[u] + 1 > dinosauraus[p]:
            dinosauraus[p] = dinosauraus[u] + 1
    heap = [(-dinosauraus[r], r) for r in roots]
    heapq.heapify(heap)
    total = 0
    for _ in range(M):
        if not heap:
            break
        taken = []
        while heap and len(taken) < K:
            taken.append(heapq.heappop(heap)[1])
        total += len(taken)
        for u in taken:
            for c in children[u]:
                heapq.heappush(heap, (-dinosauraus[c], c))
    return total


def read_your_input():
    data = sys.stdin.buffer.read().split()
    pos = 0
    T = int(data[pos]); pos += 1
    out = []
    for _ in range(T):
        N = int(data[pos]); M = int(data[pos + 1]); K = int(data[pos + 2]); pos += 3
        P = list(map(int, data[pos:pos + N])); pos += N
        out.append(str(solve(N, M, K, P)))
    print("\n".join(out))


if __name__ == "__main__":
    read_your_input()