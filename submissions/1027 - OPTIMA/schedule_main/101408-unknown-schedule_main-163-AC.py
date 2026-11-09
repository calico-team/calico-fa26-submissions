
import sys
import heapq
from collections import deque


def solve():
    input = sys.stdin.readline

    T = int(input())

    for _ in range(T):
        total_courses, M, K = map(int, input().split())
        P = list(map(int, input().split()))

        dependent_courses = [[] for _ in range(total_courses + 1)]

        for i in range(1, total_courses + 1):
            if P[i - 1] != 0:
                dependent_courses[P[i - 1]].append(i)

        # Calculate the height of every course
        height = [1] * (total_courses + 1)

        remaining = [len(dependent_courses[i]) for i in range(total_courses + 1)]

        q = deque()

        for i in range(1, total_courses + 1):
            if remaining[i] == 0:
                q.append(i)

        while q:
            u = q.popleft()

            p = P[u - 1]

            if p != 0:
                height[p] = max(height[p], height[u] + 1)

                remaining[p] -= 1

                if remaining[p] == 0:
                    q.append(p)

        # Initially available courses have no prerequisites
        available = []

        for i in range(1, total_courses + 1):
            if P[i - 1] == 0:
                heapq.heappush(available, (-height[i], i))

        answer = 0

        # Schedule courses semester by semester
        for semester in range(M):

            if not available:
                break

            next_courses = []

            # Take at most K courses this semester
            for _ in range(K):
                if not available:
                    break

                _, course = heapq.heappop(available)

                answer += 1

                # Children become available next semester
                next_courses.extend(dependent_courses[course])

            # Add newly available courses
            for course in next_courses:
                heapq.heappush(
                    available,
                    (-height[course], course)
                )

        print(answer)


if __name__ == "__main__":
    solve()
