
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
            p = P[i - 1]

            if p == 0:
                roots.append(i)
            else:
                children[p].append(i)

        # Step 1: Iterative DFS to get traversal order
        order = []
        stack = roots[:]

        while stack:
            u = stack.pop()
            order.append(u)

            for v in children[u]:
                stack.append(v)

        # Step 2: Calculate subtree sizes
        size = [1] * (N + 1)

        for u in reversed(order):
            for v in children[u]:
                size[u] += size[v]

        # Step 3: Max heap of available courses
        # Python heapq is a min heap, so use negative sizes.
        pq = [(-size[u], u) for u in roots]
        heapq.heapify(pq)

        answer = 0

        # Step 4: Simulate semesters
        for semester in range(M):
            if not pq:
                break

            completed = []

            for _ in range(K):
                if not pq:
                    break

                neg_size, u = heapq.heappop(pq)

                answer += 1
                completed.append(u)

            # Make children available NEXT semester
            for u in completed:
                for v in children[u]:
                    heapq.heappush(pq, (-size[v], v))

        print(answer)


if __name__ == "__main__":
    solve()
