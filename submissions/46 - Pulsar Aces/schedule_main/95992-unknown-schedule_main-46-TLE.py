def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.
    
    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
    """
    p = set()
    p.add(0)
    r = 0
    g = 0
    for _ in range(M):
        t = set()
        for i in range(N):
            if P[i] in p and i+1 not in p:
                t.add(i+1)
                g += 1
        p |= t
        h = min(g, K)
        r += h
        g -= h
    return r


def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()