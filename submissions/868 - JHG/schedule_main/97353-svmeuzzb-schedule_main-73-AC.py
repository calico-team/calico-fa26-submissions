from collections import deque


def solve():
    num_tests = int(input().strip())

    for _ in range(num_tests):
        N, M, K = map(int, input().split())

        prerequisites = list(map(int, input().split()))

        children = {i: [] for i in range(N + 1)}
        roots = []

        for child_idx in range(1, N + 1):
            parent = prerequisites[child_idx - 1]
            if parent == 0:
                roots.append(child_idx)
            else:
                children[parent].append(child_idx)

        level_counts = [0] * (N + 1)
        queue = deque([(root, 0) for root in roots])

        while queue:
            curr, lvl = queue.popleft()
            if lvl < N + 1:
                level_counts[lvl] += 1
            for nxt in children[curr]:
                queue.append((nxt, lvl + 1))

        total_courses_taken = 0
        currently_available = 0

        for m in range(M):
            if m < len(level_counts):
                currently_available += level_counts[m]

            taken = min(currently_available, K)
            total_courses_taken += taken
            currently_available -= taken

        print(total_courses_taken)


solve()
