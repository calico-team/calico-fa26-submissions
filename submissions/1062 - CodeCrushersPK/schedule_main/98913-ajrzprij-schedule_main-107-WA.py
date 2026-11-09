def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.
    
    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a pre_requisite array for classes 1 to N (0 if there are no pre_requisite classes)
    """
    agly_courses = [[] for _ in range(N + 1)]
    for i in range(1, N + 1):
        pre_req = P[i - 1]
        if pre_req != 0:
            agly_courses[pre_req].append(i)
    option = []
    for i in range(1, N + 1):
        if P[i - 1] == 0:
            option.append(i)
    complete_waly = 0
    for ascdnjcd in range(M):
        if not option:
            break
        option.sort(key=lambda x: len(agly_courses[x]), reverse=True)
        is_semester_ky_courses = option[:K]
        option = option[K:] 
        for course in is_semester_ky_courses:
            complete_waly += 1
            for agla in agly_courses[course]:
                option.append(agla)
    return complete_waly

def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()