def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.
    
    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
    """
    # YOUR CODE HERE

    dpndnts = [[] for _ in range(N + 1)]
    in_deg = [0] * (N + 1)

    for i in range(1, N+1):
        prereq = P[i-1]
        if prereq != 0:
            dpndnts[prereq].append(i)
            in_deg[i] = 1

    ready = []
    for i in range(1, N+1):
        if in_deg[i] == 0:
            ready.append(i)

    completed = 0

    for semester in range(M):
        if not ready:
            break
        can_take = min(K,len(ready))
        taken_this_semester = ready[:can_take]
        ready = ready[can_take:]
        completed += can_take

        for cls in taken_this_semester:
            for dpn in dpndnts[cls]:
                in_deg[dpn]-=1
                if in_deg[dpn]==0:
                    ready.append(dpn)

    return completed

def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()