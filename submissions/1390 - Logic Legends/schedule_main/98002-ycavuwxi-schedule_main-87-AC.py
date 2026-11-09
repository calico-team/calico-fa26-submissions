import heapq
 
 
def solve(N, M, K, P):
    children = [[] for _ in range(N + 1)]
    for i in range(1, N + 1):
        children[P[i - 1]].append(i)
    order = []
    stack = [0]
    while stack:
        u = stack.pop()
        order.append(u)
        stack.extend(children[u])
    height = [1] * (N + 1)
    for u in reversed(order):
        for v in children[u]:
            if height[v] + 1 > height[u]:
                height[u] = height[v] + 1
    heap = [(-height[v], v) for v in children[0]]
    heapq.heapify(heap)
    taken = 0
    for _ in range(M):
        if not heap:
            break
        batch = []
        while heap and len(batch) < K:
            batch.append(heapq.heappop(heap)[1])
        taken += len(batch)
        for u in batch:
            for v in children[u]:
                heapq.heappush(heap, (-height[v], v))
    return taken
 
 
def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))
 
 
if __name__ == '__main__':
    main()