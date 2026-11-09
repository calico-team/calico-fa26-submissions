def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.
    
    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
    """
    # YOUR CODE HERE
    if M <= 0 or K <= 0:
        return 0

    dependents = []
    for i in range(N + 1):
        dependents.append([])

    for course in range(1, N + 1):
        prereq = P[course - 1]
        if prereq != 0:
            dependents[prereq].append(course)

    depth = []
    for i in range(N + 1):
        depth.append(0)

    queue = []
    for course in range(1, N + 1):
        if P[course - 1] == 0:
            depth[course] = 1
            queue.append(course)

    front = 0
    while front < len(queue):
        current = queue[front]
        front = front + 1
        for dependent in dependents[current]:
            depth[dependent] = depth[current] + 1
            queue.append(dependent)

    levels = []
    for course in range(1, N + 1):
        if depth[course] >= 1 and depth[course] <= M:
            levels.append(depth[course])
    levels.sort()

    semester = 1
    used = 0
    answer = 0

    for level in levels:
        if semester < level:
            semester = level
            used = 0
        if used == K:
            semester = semester + 1
            used = 0
            if semester < level:
                semester = level
                used = 0
        if semester > M:
            break
        used = used + 1
        answer = answer + 1

    return answer

def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()