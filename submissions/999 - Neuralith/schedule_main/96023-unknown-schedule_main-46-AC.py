
import sys
import heapq

input = sys.stdin.readline


def solve():
    T = int(input())

    for _ in range(T):
        N, M, K = map(int, input().split())
        P = list(map(int, input().split()))

        children = [[] for _ in range(N)]
        parent = [-1] * N

        for i in range(N):
            if P[i] != 0:
                p = P[i] - 1
                parent[i] = p
                children[p].append(i)

        # Step 1: Calculate subtree heights using leaf removal
        remaining = [len(children[i]) for i in range(N)]
        height = [1] * N

        queue = []

        for i in range(N):
            if remaining[i] == 0:
                queue.append(i)

        # Process leaves before their parents
        for v in queue:
            p = parent[v]

            if p != -1:
                height[p] = max(height[p], height[v] + 1)

                remaining[p] -= 1

                if remaining[p] == 0:
                    queue.append(p)

        # Step 2: Initialize max heap with root courses
        heap = []

        for i in range(N):
            if parent[i] == -1:
                heapq.heappush(heap, (-height[i], i))

        # Step 3: Schedule courses semester by semester
        answer = 0

        for semester in range(M):

            if not heap:
                break

            selected = []

            # Select at most K available courses
            for _ in range(min(K, len(heap))):
                neg_h, v = heapq.heappop(heap)
                selected.append(v)

            answer += len(selected)

            # Unlock children for the next semester
            for v in selected:
                for child in children[v]:
                    heapq.heappush(
                        heap,
                        (-height[child], child)
                    )

        print(answer)


if __name__ == "__main__":
    solve()
