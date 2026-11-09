import heapq


def solve(N, M, K, P):
    kids = [[] for _ in range(N + 1)]
    for i in range(1, N + 1):
        kids[P[i - 1]].append(i)

    order = []
    stack = [0]
    while stack:
        x = stack.pop()
        order.append(x)
        stack.extend(kids[x])

    h = [1] * (N + 1)
    for x in reversed(order):
        for c in kids[x]:
            if h[c] + 1 > h[x]:
                h[x] = h[c] + 1

    heap = [(-h[c], c) for c in kids[0]]
    heapq.heapify(heap)

    taken = 0
    for _ in range(M):
        if not heap:
            break
        got = []
        while heap and len(got) < K:
            got.append(heapq.heappop(heap)[1])
        taken += len(got)
        for g in got:
            for c in kids[g]:
                heapq.heappush(heap, (-h[c], c))

    return taken


def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))


if __name__ == '__main__':
    main()
