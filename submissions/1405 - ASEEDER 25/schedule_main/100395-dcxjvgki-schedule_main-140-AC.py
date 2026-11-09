import sys
from heapq import heapify, heappop, heappush


def maximum_courses(n, semesters, per_semester, prerequisites):
    children = [[] for _ in range(n)]
    roots = []

    for course, prerequisite in enumerate(prerequisites):
        if prerequisite == 0:
            roots.append(course)
        else:
            children[prerequisite - 1].append(course)

    # Obtain a parent-before-child ordering of the prerequisite forest.
    order = []
    stack = roots[:]
    while stack:
        course = stack.pop()
        order.append(course)
        stack.extend(children[course])

    # Height is the length of the longest chain starting at this course.
    height = [0] * n
    for course in reversed(order):
        longest_child = 0
        for child in children[course]:
            longest_child = max(longest_child, height[child])
        height[course] = longest_child + 1

    # Available courses with longer remaining chains have higher priority.
    available = [(-height[course], course) for course in roots]
    heapify(available)
    completed = 0

    for _ in range(min(semesters, n)):
        selected = []
        for _ in range(min(per_semester, len(available))):
            selected.append(heappop(available)[1])

        if not selected:
            break

        completed += len(selected)

        # Children become available only in the following semester.
        for course in selected:
            for child in children[course]:
                heappush(available, (-height[child], child))

        if completed == n:
            break

    return completed


def solve():
    input = sys.stdin.buffer.readline
    test_cases = int(input())
    answers = []

    for _ in range(test_cases):
        n, semesters, per_semester = map(int, input().split())
        prerequisites = list(map(int, input().split()))
        answers.append(str(maximum_courses(
            n, semesters, per_semester, prerequisites
        )))

    sys.stdout.write("\n".join(answers))


if __name__ == "__main__":
    solve()
