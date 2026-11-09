def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.
    
    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
    """
    max_class = 0
    sem = 0
    while sem < M:
        if P.count(min(P)) == 1:
            max_class += 1
        if P.count(max(P)) == 1 and max(P) - 1 in P == None:
            max_class += 1
        if P.count(min(P)) >= 1: 
            max_class += P.count(min(P)) + (P.count(min(P)) - K)
        sem += 1
        
    return max_class

def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()