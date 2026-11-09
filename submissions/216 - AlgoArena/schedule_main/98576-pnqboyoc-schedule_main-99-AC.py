def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.
    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
    """
    pre_requisite = [0] + P
    levels = [0] * (N + 1)
    for i in range(1, N + 1):
        curr, d = i, 0
        while pre_requisite[curr]:
            curr = pre_requisite[curr]
            d += 1
        levels[i] = d
    max_l = max(levels) if N else 0
    level_counts = [0] * (max_l + 1)
    for l in levels[1:]:
        level_counts[l] += 1
    ans = 0
    pool = 0
    for sem in range(M):
        if sem <= max_l:
            pool += level_counts[sem]
        take = min(pool, K)
        ans += take
        pool -= take
    return ans
def main():
    for _ in range(int(input())):
        parts = input().split()
        N, M, K = int(parts[0]), int(parts[1]), int(parts[2])
        P = [int(x) for x in input().split()]
        print(solve(N, M, K, P))
if __name__ == '__main__':
    main()