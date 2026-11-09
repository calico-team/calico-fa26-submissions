import sys
import heapq


def solve():
    input = sys.stdin.readline

    T = int(input())

    for _ in range(T):
        N, M, K = map(int, input().split())
        P = list(map(int, input().split()))

        # Build the prerequisite tree
        children = [[] for _ in range(N)]
        roots = []

        for i in range(N):
            if P[i] == 0:
                roots.append(i)
            else:
                parent = P[i] - 1
                children[parent].append(i)

        # Calculate heights using iterative traversal
        order = []
        stack = roots[:]

        while stack:
            u = stack.pop()
            order.append(u)

            for v in children[u]:
                stack.append(v)

        height = [1] * N

        for u in reversed(order):
            for v in children[u]:
                height[u] = max(
                    height[u],
                    height[v] + 1
                )

        # Max heap: prioritize courses with greater height
        pq = [(-height[u], u) for u in roots]
        heapq.heapify(pq)

        answer = 0

        # Process semesters
        for semester in range(M):

            next_courses = []

            # Take at most K available courses
            for _ in range(min(K, len(pq))):
                neg_h, u = heapq.heappop(pq)

                answer += 1

                # Children become available next semester
                next_courses.extend(children[u])

            # Add newly available courses
            for v in next_courses:
                heapq.heappush(pq, (-height[v], v))

            if not pq:
                break

        print(answer)


if __name__ == "__main__":
    solve()