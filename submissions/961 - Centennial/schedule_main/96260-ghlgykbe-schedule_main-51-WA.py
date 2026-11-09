def solve(courses: int, semesters: int, maxSemester: int, pre: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.

    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
    """

    completed = []
    for _ in range(semesters):
        taken = []
        for course in range(1, courses + 1):
            if course in completed or course in taken:
                continue

            req = pre[course - 1]
            if req == 0 or req in completed and course not in taken:
                taken.append(course)
                if len(taken) == maxSemester:
                    break

        completed.extend(taken)
        if len(completed) == courses:
            break

    return len(completed)

def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()