
from collections import deque

def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.
    
    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
    """
    # YOUR CODE HERE

    courses = [[] for i in range(N + 1)]
    for i in range(1, N + 1):
        if P[i - 1] != 0:
            courses[P[i - 1]].append(i)
    height = [1] * (N + 1)
    left = [len(courses[i]) for i in range(N + 1)]



    q = deque()

    for i in range(1, N + 1):
        if left[i] == 0:
            q.append(i)

    while q:
        a = q.popleft()
        p = P[a - 1]

        if p != 0:
            height[p] = max(height[p], height[a] + 1)
            left[p] -= 1

            if left[p] == 0:
                q.append(p)

    groups = [[] for i in range(max(height) + 1)]

    biggest = 0

    for i in range(1, N + 1):

        if P[i - 1] == 0:
            groups[height[i]].append(i)
            biggest = max(biggest, height[i])

    ans = 0

    for i in range(M):
        taken = []

        for j in range(K):

            while biggest > 0 and not groups[biggest]:
                biggest -= 1

            if biggest == 0:
                break

            a = groups[biggest].pop()
            taken.append(a)
            ans += 1

        for a in taken:
            for b in courses[a]:
                groups[height[b]].append(b)
                biggest = max(biggest, height[b])

        if biggest == 0:
            break

    return ans




def main():
    T = int(input())
    for i in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()
