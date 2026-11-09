import sys
import heapq

def solve():
    input = sys.stdin.readline

    T = int(input())

    for _ in range(T):
        N, M, K = map(int, input().split())
        P = list(map(int, input().split()))

        children = [[] for _ in range(N + 1)]
        roots = []

        for i in range(1, N + 1):
            if P[i - 1] == 0:
                roots.append(i)
            else:
                children[P[i - 1]].append(i)

        # Calculate subtree sizes
        order = []
        stack = roots[:]

        while stack:
            u = stack.pop()
            order.append(u)
            for v in children[u]:
                stack.append(v)

        size = [1] * (N + 1)

        for u in reversed(order):
            for v in children[u]:
                size[u] += size[v]

        # Max heap of currently available courses
        available = []

        for u in roots:
            heapq.heappush(available, (-size[u], u))

        answer = 0

        # Process each semester
        for semester in range(M):
            if not available:
                break

            selected = []

            for _ in range(min(K, len(available))):
                neg_size, u = heapq.heappop(available)
                selected.append(u)
                answer += 1

            # Children become available next semester
            for u in selected:
                for v in children[u]:
                    heapq.heappush(
                        available, (-size[v], v)
                    )

        print(answer)


if __name__ == "__main__":
    solve()
