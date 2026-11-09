import sys
import heapq

input = sys.stdin.readline

t = int(input())
answers = []

for _ in range(t):
    n, m, k = map(int, input().split())
    prereq = list(map(int, input().split()))

    children = [[] for _ in range(n)]
    roots = []

    for course in range(n):
        parent = prereq[course] - 1

        if parent == -1:
            roots.append(course)
        else:
            children[parent].append(course)

    # Get an order where every parent appears before its children.
    order = []
    stack = roots[:]

    while stack:
        course = stack.pop()
        order.append(course)

        for child in children[course]:
            stack.append(child)

    # Height is the longest chain starting at each course.
    height = [1] * n

    for course in reversed(order):
        for child in children[course]:
            height[course] = max(height[course], height[child] + 1)

    # Available courses, ordered by longest remaining chain.
    ready = []

    for course in roots:
        heapq.heappush(ready, (-height[course], course))

    taken = 0

    # There is no need to simulate more than N semesters.
    for _ in range(min(m, n)):
        finished_now = []
        count = min(k, len(ready))

        for _ in range(count):
            _, course = heapq.heappop(ready)
            taken += 1
            finished_now.append(course)

        # These courses' dependents are available next semester.
        for course in finished_now:
            for child in children[course]:
                heapq.heappush(ready, (-height[child], child))

    answers.append(str(taken))

print("\n".join(answers))