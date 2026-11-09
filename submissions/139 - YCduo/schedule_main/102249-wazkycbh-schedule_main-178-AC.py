def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.
    
    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
    """
    # YOUR CODE HERE
    depth = {}
    for i in range(1, N + 1):
        path = []
        while (i != 0) and i not in depth:
            path.append(i)
            i = P[i - 1]
        for j in reversed(path):
            depth[j] = depth.get(P[j - 1], 0) + 1
    return (min([N] + [i + K * (M - j + 1) for i, j in enumerate(sorted(depth.values())) if j <= M + 1]))

def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()