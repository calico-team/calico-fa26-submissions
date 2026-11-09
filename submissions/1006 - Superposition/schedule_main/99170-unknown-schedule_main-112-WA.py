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
    
    for semester in range(M):
        if classes_taken == N:
            break
    
        available = []
        
        for i in range(N):
            course_id = i + 1
            pre_req = P[i]
            
            if not completed_courses[course_id]:
                if (pre_req == 0) or completed_courses[pre_req]:
                    available.append(course_id)
                    
        courses_left = min(K, len(available))
        
        
        
        for j in range(courses_left):
            course = available[j]
            completed_courses[course] = True
            classes_taken += 1
    
    
    
    
    
    return classes_taken

def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()