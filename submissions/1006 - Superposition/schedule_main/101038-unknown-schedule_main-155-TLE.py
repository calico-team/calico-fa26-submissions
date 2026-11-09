def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.
    
    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
    """
    # YOUR CODE HERE
    courses_taken = set()
    depends_on = [[] for _ in range(N + 1)]
    
    
    for i in range(N):
        course_id = i + 1
        prereq = P[i]
        if prereq != 0:
            depends_on[prereq].append(course_id)
            
    
    depth = [0] * (N + 1)
    
    for _ in range(1000): 
        changed = False
        for i in range(1, N + 1):
            max_dep_depth = 0
            for dep in depends_on[i]:
                max_dep_depth = max(max_dep_depth, depth[dep])
            
            new_depth = 1 + max_dep_depth
            if depth[i] != new_depth:
                depth[i] = new_depth
                changed = True
        if not changed:
            break

    
    
    for semester in range(M):
        if len(courses_taken) == N:
            break
            
        available = []
        for i in range(N):
            course_id = i + 1
            if course_id not in courses_taken:
                pre_req = P[i]
                if pre_req == 0 or pre_req in courses_taken:
                    available.append(course_id)
        
        if not available:
            break
            
        
        
        # lets see what happens
        available.sort(key=lambda x: depth[x], reverse=True)
        num_to_take = min(K, len(available))
        for j in range(num_to_take):
            courses_taken.add(available[j])
            
            
            
            
    return len(courses_taken)

def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()