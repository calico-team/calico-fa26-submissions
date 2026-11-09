
import sys
import heapq


def solve(N: int, M: int, K: int, P: list[int]) -> int:
    children = [[] for _ in range(N)]
    roots = []

    for i, p in enumerate(P):
        if p == 0:
            roots.append(i)
        else:
            children[p - 1].append(i)

    order = []
    stack = roots[:]

    while stack:
        u = stack.pop()
        order.append(u)
        stack.extend(children[u])

    subtree = [1] * N
    height = [1] * N

    for u in reversed(order):
        for v in children[u]:
            subtree[u] += subtree[v]
            height[u] = max(height[u], height[v] + 1)

    available = []
    for u in roots:
        heapq.heappush(available, (-subtree[u], -height[u], u))

    answer = 0

    for semester in range(M):
        if not available:
            break

        chosen = []

        for _ in range(min(K, len(available))):
            _, _, u = heapq.heappop(available)
            chosen.append(u)

        answer += len(chosen)

        for u in chosen:
            for v in children[u]:
                heapq.heappush(
                    available, (-subtree[v], -height[v], v)
                )

    return answer


def main():
    input = sys.stdin.readline
    T = int(input())

    for _ in range(T):
        N, M, K = map(int, input().split())
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))


if __name__ == "__main__":
    main()
