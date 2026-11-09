
import heapq

def solve(N: int, M: int, K: int, P: list[int]) -> int:

    # Step 1: Build prerequisite tree
    children = [[] for _ in range(N)]
    roots = []

    for i in range(N):
        if P[i] == 0:
            roots.append(i)
        else:
            parent = P[i] - 1
            children[parent].append(i)

    # Step 2: Get traversal order
    order = []
    stack = roots[:]

    while stack:
        node = stack.pop()
        order.append(node)

        for child in children[node]:
            stack.append(child)

    # Step 3: Calculate longest remaining chain (height)
    height = [1] * N

    for node in reversed(order):
        for child in children[node]:
            height[node] = max(
                height[node],
                height[child] + 1
            )

    # Step 4: Max Heap of available courses
    # Higher height gets higher priority
    available = []

    for node in roots:
        heapq.heappush(
            available,
            (-height[node], node)
        )

    # Step 5: Take courses semester by semester
    total = 0

    for semester in range(M):

        if not available:
            break

        batch = []

        # Take at most K available courses
        for _ in range(K):

            if not available:
                break

            _, node = heapq.heappop(available)

            total += 1
            batch.append(node)

        # Children become available in the NEXT semester
        for node in batch:
            for child in children[node]:
                heapq.heappush(
                    available,
                    (-height[child], child)
                )

        if total == N:
            break

    return total


def main():
    T = int(input())

    for _ in range(T):
        N, M, K = map(int, input().split())
        P = list(map(int, input().split()))

        print(solve(N, M, K, P))


if __name__ == '__main__':
    main()
