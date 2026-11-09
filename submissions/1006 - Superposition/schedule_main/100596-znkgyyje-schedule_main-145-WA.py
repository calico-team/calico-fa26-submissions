def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.
    
    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
    """
    # YOUR CODE HERE
    completed_courses = [False] * (N+1)
    classes_taken = 0

    available = []
    depends_on = [[] for _ in range(N + 1)]

    
    prereq_left = [0] * (N + 1)

    for i in range(N):
        course_id = i + 1
        pre_req = P[i]

        if pre_req == 0:
            available.append(course_id)
        else:
            depends_on[pre_req].append(course_id)
            prereq_left[course_id] += 1

    
    
    for semester in range(M):
        if classes_taken == N:
            break

        if not available:
            break

        courses_left = min(K, len(available))

        this_sem_taken = available[:courses_left]
        available = available[courses_left:]

        
        for course in this_sem_taken:
            completed_courses[course] = True
            classes_taken += 1

            for c in depends_on[course]:
                prereq_left[c] -= 1
                if prereq_left[c] == 0:
                    available.append(c)

    
    
    return classes_taken

def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()