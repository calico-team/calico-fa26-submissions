def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.
    
    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
    """
    # YOUR CODE HERE
    completed = [False] * (N+1)
    classes_taken = 0

    prereq_left = [0] * (N + 1)
    dependents = [[] for _ in range(N + 1)]

    for i in range(1, N + 1):
        pre_req = P[i - 1]
        if pre_req != 0:
            prereq_left[i] += 1
            dependents[pre_req].append(i)

    
    
    available = []
    for i in range(1, N + 1):
        if prereq_left[i] == 0:
            available.append(i)

    for semester in range(M):
        if classes_taken == N or not available:
            break

        courses_this_sem = min(K, len(available))
        taken = available[:courses_this_sem]
        available = available[courses_this_sem:]

        for course in taken:
            completed[course] = True
            classes_taken += 1
            
            
            for dep in dependents[course]:
                prereq_left[dep] -= 1
                if prereq_left[dep] == 0:
                    available.append(dep)

    
    
    return classes_taken

def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()