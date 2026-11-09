test_cases = int(input())

for case in range(test_cases):
    n, semesters, limit = map(int, input().split())
    prerequisite = [0] + list(map(int, input().split()))
    earliest = [0] * (n + 1)

    for start in range(1, n + 1):
        if earliest[start] != 0:
            continue

        path = []
        course = start

        while course != 0 and earliest[course] == 0:
            path.append(course)
            course = prerequisite[course]

        while path:
            course = path.pop()
            previous_course = prerequisite[course]
            earliest[course] = earliest[course] + 1

    counts = [0] * (n + 1)
    for course in range(1, n + 1):
        counts[earliest[course]] += 1
    
    answer = min(n, semesters * limit)
    available = 0

    for semester in range(1, min(semesters, n) + 1):
        available += counts[semester]
        remaining_semester = semesters - semester
        upper_bound = available + remaining_semester * limit
        answer = min(answer, upper_bound)

    print(answer)