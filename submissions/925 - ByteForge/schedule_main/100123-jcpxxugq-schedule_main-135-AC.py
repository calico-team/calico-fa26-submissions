import heapq

def solve(N: int, M: int, K: int, P: list[int]) -> int:

    childrn = [[] for _ in range(N + 1)]
    for i in range(1, N + 1):
        childrn[P[i - 1]].append(i)

    height = [0] * (N + 1)
    order = []
    stack = [0]
    while stack:
        u = stack.pop()
        order.append(u)
        for v in childrn[u]:
            stack.append(v)

    for u in reversed(order):
        h = 1
        for v in childrn[u]:
            if height[v] + 1 > h:
                h = height[v] + 1
        height[u] = h

    heap = []
    for root in childrn[0]:
        heapq.heappush(heap, (-height[root], root))

    total = 0
    for _ in range(M):
        if not heap:
            break
        count = min(K, len(heap))
        popped = []
        for _ in range(count):
            _, u = heapq.heappop(heap)
            popped.append(u)
        total += count
        for u in popped:
            for v in childrn[u]:
                heapq.heappush(heap, (-height[v], v))

    return total

def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()