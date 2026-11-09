
import heapq
from collections import deque

def solve():
    T = int(input())

    for _ in range(T):
        N, M, K = map(int, input().split())
        P = [0] + list(map(int, input().split()))

        children = [[] for _ in range(N + 1)]
        remaining = [0] * (N + 1)

        # Build prerequisite tree
        for i in range(1, N + 1):
            if P[i] != 0:
                children[P[i]].append(i)
                remaining[P[i]] += 1

        # Calculate longest chain from each course
        height = [1] * (N + 1)

        queue = deque(
            i for i in range(1, N + 1)
            if remaining[i] == 0
        )

        while queue:
            course = queue.popleft()
            parent = P[course]

            if parent != 0:
                height[parent] = max(
                    height[parent],
                    height[course] + 1
                )

                remaining[parent] -= 1

                if remaining[parent] == 0:
                    queue.append(parent)

        # Initially available courses
        heap = []

        for i in range(1, N + 1):
            if P[i] == 0:
                heapq.heappush(heap, (-height[i], i))

        answer = 0

        # Schedule semesters
        for semester in range(M):
            if not heap:
                break

            current = []

            # Select up to K available courses
            for _ in range(min(K, len(heap))):
                _, course = heapq.heappop(heap)
                current.append(course)

            answer += len(current)

            # Unlock courses for the NEXT semester
            for course in current:
                for child in children[course]:
                    heapq.heappush(
                        heap, (-height[child], child)
                    )

        print(answer)


if __name__ == "__main__":
    solve()
