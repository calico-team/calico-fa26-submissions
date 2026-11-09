import sys
import heapq


def solve(N: int, M: int, K: int, P: list[int]) -> int:
    adj = [[] for _ in range(N + 1)]
    new_roots = []

    for i in range(1, N + 1):
        if P[i - 1] == 0:
            new_roots.append(i)
        else:
            adj[P[i - 1]].append(i)

    # Get an order in which parents come before children
    order = []
    stack = new_roots[:]

    while stack:
        u = stack.pop()
        order.append(u)

        for v in adj[u]:
            stack.append(v)

    # Calculate the longest chain starting from each course
    current_height = [0] * (N + 1)

    for u in reversed(order):
        best = 0

        for v in adj[u]:
            best = max(best, current_height[v])

        current_height[u] = best + 1

    # Courses with longer chains get higher priority
    heap = [(-current_height[u], u) for u in new_roots]
    heapq.heapify(heap)

    ans = 0

    for _ in range(min(M, N)):
        if not heap:
            break

        taken = []

        for _ in range(min(K, len(heap))):
            _, u = heapq.heappop(heap)
            taken.append(u)

        ans += len(taken)

        # Make their dependent courses available next semester
        for u in taken:
            for v in adj[u]:
                heapq.heappush(heap, (-current_height[v], v))

    return ans


def main():
    input = sys.stdin.readline

    T = int(input())

    for _ in range(T):
        N, M, K = map(int, input().split())
        P = list(map(int, input().split()))

        print(solve(N, M, K, P))


if __name__ == "__main__":
    main()