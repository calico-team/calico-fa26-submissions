import sys
import heapq


def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    test_cases = data[0]
    pos = 1
    answers = []

    for _ in range(test_cases):
        n, semesters, limit = data[pos:pos + 3]
        pos += 3
        prerequisites = data[pos:pos + n]
        pos += n

        children = [[] for _ in range(n)]
        roots = []

        for course, prerequisite in enumerate(prerequisites):
            if prerequisite == 0:
                roots.append(course)
            else:
                children[prerequisite - 1].append(course)

        order = []
        stack = roots[:]

        while stack:
            course = stack.pop()
            order.append(course)
            stack.extend(children[course])

        subtree_size = [1] * n
        for course in reversed(order):
            prerequisite = prerequisites[course]
            if prerequisite:
                subtree_size[prerequisite - 1] += subtree_size[course]

        available = [(-subtree_size[course], course) for course in roots]
        heapq.heapify(available)

        completed = 0

        for _ in range(semesters):
            if not available:
                break

            taken = []
            for _ in range(min(limit, len(available))):
                _, course = heapq.heappop(available)
                taken.append(course)

            completed += len(taken)

            for course in taken:
                for following in children[course]:
                    heapq.heappush(
                        available,
                        (-subtree_size[following], following)
                    )

        answers.append(str(completed))

    sys.stdout.write("\n".join(answers))


if __name__ == "__main__":
    main()