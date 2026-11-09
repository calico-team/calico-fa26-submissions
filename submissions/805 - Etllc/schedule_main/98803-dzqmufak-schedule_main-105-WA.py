import sys
from collections import deque

def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    test_cases = data[0]
    pos = 1
    answers = []

    for _ in range(test_cases):
        n, semesters, limit = data[pos], data[pos + 1], data[pos + 2]
        pos += 3

        prerequisites = data[pos:pos + n]
        pos += n

        next_course = [[] for _ in range(n + 1)]
        available = deque()

        for course, prerequisite in enumerate(prerequisites, start=1):
            if prerequisite == 0:
                available.append(course)
            else:
                next_course[prerequisite].append(course)

        completed = 0

        for _ in range(semesters):
            if not available:
                break

            courses_this_semester = min(limit, len(available))
            taken = [available.popleft() for _ in range(courses_this_semester)]
            completed += courses_this_semester

            for course in taken:
                available.extend(next_course[course])

        answers.append(str(completed))

    sys.stdout.write("\n".join(answers))

if __name__ == "__main__":
    main()