import heapq
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
    child = [[] for _ in range(N + 1)]
    deg = [0] * (N + 1)
    ht = [1] * (N + 1)

    for i in range(1, N + 1):
        if P[i - 1] != 0:
            child[P[i - 1]].append(i)
            deg[P[i - 1]] += 1

    q = deque()

    for i in range(1, N + 1):
        if deg[i] == 0:
            q.append(i)

    while q:
        u = q.popleft()
        p = P[u - 1]

        if p != 0:
            ht[p] = max(ht[p], ht[u] + 1)
            deg[p] -= 1

            if deg[p] == 0:
                q.append(p)

    present = []

    for i in range(1, N + 1):
        if P[i - 1] == 0:
            heapq.heappush(present, (-ht[i], i))

    ans = 0

    for _ in range(M):
        selected = []

        for _ in range(K):
            if not present:
                break

            _, u = heapq.heappop(present)
            selected.append(u)
            ans += 1

        for u in selected:
            for v in child[u]:
                heapq.heappush(present, (-ht[v], v))

        if not present:
            break

    return ans

def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()