import sys
from collections import deque


def find_minimum(parents, total_terms, term_limit):
    course_count = len(parents)

    dependency_map = [[] for _ in range(course_count + 1)]

    for subject, requirement in enumerate(parents, 1):
        dependency_map[requirement].append(subject)

    pending_courses = deque(dependency_map[0])

    finished_courses = 0
    minimum_result = course_count
    available_terms = total_terms

    while pending_courses:

        achievable = finished_courses + available_terms * term_limit
        minimum_result = min(minimum_result, achievable)

        if available_terms <= 0:
            break

        current_batch = len(pending_courses)

        for position in range(current_batch):
            subject = pending_courses.popleft()

            for next_subject in dependency_map[subject]:
                pending_courses.append(next_subject)

        finished_courses += current_batch
        available_terms -= 1

    return minimum_result


def run_program():
    input_values = iter(map(int, sys.stdin.buffer.read().split()))

    test_count = next(input_values)
    output_lines = []

    for case_number in range(test_count):
        course_count = next(input_values)
        term_count = next(input_values)
        max_courses = next(input_values)

        prerequisite_list = [
            next(input_values) for _ in range(course_count)
        ]

        result = find_minimum(
            prerequisite_list,
            term_count,
            max_courses
        )

        output_lines.append(str(result))

    print("\n".join(output_lines))


if __name__ == "__main__":
    run_program()