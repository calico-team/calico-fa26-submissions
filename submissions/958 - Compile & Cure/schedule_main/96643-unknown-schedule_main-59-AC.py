import heapq


def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.

    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
    """
    kids = [[] for _ in range(N + 1)]
    for i in range(N):
        kids[P[i]].append(i + 1)

    order = []
    stack = [0]
    while stack:
        node = stack.pop()
        order.append(node)
        for c in kids[node]:
            stack.append(c)

    height = [0] * (N + 1)
    for node in reversed(order):
        best = 0
        for c in kids[node]:
            if height[c] > best:
                best = height[c]
        height[node] = best + 1

    ready = []
    for c in kids[0]:
        heapq.heappush(ready, (-height[c], c))

    total = 0
    for _ in range(M):
        if not ready:
            break
        today = []
        while ready and len(today) < K:
            today.append(heapq.heappop(ready))
        total += len(today)
        for _, node in today:
            for c in kids[node]:
                heapq.heappush(ready, (-height[c], c))

    return total


def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))


if __name__ == '__main__':
    main()