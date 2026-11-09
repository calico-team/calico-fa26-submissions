def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.
    
    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
    """
    # YOUR CODE HERE
def solve(N: int, M: int, K: int, P: list[int]) -> int:

    course = [[] for a in range(N)]
    no_pr=[]

    for i in range(N):
        p_r = P[i]

        if p_r == 0:
            no_pr.append(i)
        else:
            course[p_r - 1].append(i)

    print(course)
    print(no_pr)

    return 0

def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()