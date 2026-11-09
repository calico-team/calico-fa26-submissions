# Source: https://usaco.guide/general/io
import sys
import heapq

def solve():
    data = list(map(int, sys.stdin.buffer.read().split()))
    it = iter(data)
    t = next(it)
    answers = []

    for _ in range(t):
        n = next(it)
        m = next(it)
        k = next(it)
        prereq = [next(it) for _ in range(n)]

        children = [[] for _ in range(n)]
        roots = []

        for course, p in enumerate(prereq):
            if p == 0:
                roots.append(course)
            else:
                children[p - 1].append(course)

        order = []
        stack = roots[:]
        while stack:
            u = stack.pop()
            order.append(u)
            stack.extend(children[u])

        subtree = [1] * n
        for u in reversed(order):
            for v in children[u]:
                subtree[u] += subtree[v]

        available = [(-subtree[u], u) for u in roots]
        heapq.heapify(available)
        taken = 0

        for _ in range(m):
            next_semester = []
            for _ in range(min(k, len(available))):
                _, u = heapq.heappop(available)
                taken += 1
                for v in children[u]:
                    next_semester.append((-subtree[v], v))
            for course in next_semester:
                heapq.heappush(available, course)

            if taken == n:
                break

        answers.append(str(taken))

    sys.stdout.write("\n".join(answers))

if __name__ == "__main__":
    solve()
