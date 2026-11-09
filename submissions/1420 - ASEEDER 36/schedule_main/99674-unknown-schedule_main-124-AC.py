import  sys

data = sys.stdin.buffer.read().split()
pos = 0

test_cases = int(data[pos])
pos +=1
output = []

for case in range(test_cases):
    n = int(data[pos])
    semesters = int(data[pos + 1])
    limit = int(data[pos + 2])
    pos += 3
    prerequisite = [0] + [int(x) for x in data[pos:pos + n]]
    pos += n

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
            earliest[course] = earliest[previous_course] + 1

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

    output.append(str(answer))

print("\n".join(output))