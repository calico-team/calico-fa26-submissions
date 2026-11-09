from collections import deque
import heapq

def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.
    
    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
    """

    candidates = [[] for _ in range(N + 1)]
    in_degree = [0] * (N + 1)

    for major in range(1, N + 1):
        parent = P[major - 1]

        if parent != 0:
            candidates[parent].append(major)
            in_degree[major] = 1

    roots = [
        i for i in range(1, N + 1)
        if in_degree[i] == 0
    ]

    sequence = []
    queue = deque(roots)

    while queue:
        major = queue.popleft()
        sequence.append(major)

        for child in candidates[major]:
            queue.append(child)

    height = [1] * (N + 1)

    for major in reversed(sequence):
        for child in candidates[major]:
            height[major] = max(
                height[major],
                height[child] + 1
            )

    available = []

    for major in roots:
        heapq.heappush(
            available, (-height[major], major)
        )

    completed = 0

    for semester in range(M):
        if not available:
            break

        selected = []

        for _ in range(min(K, len(available))):
            _, major = heapq.heappop(available)
            selected.append(major)

        completed += len(selected)

        for major in selected:
            for child in candidates[major]:
                heapq.heappush(
                    available, (-height[child], child)
                )

    return completed

def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()