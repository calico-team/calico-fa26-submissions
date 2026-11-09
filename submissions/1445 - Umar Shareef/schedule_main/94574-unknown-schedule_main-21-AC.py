import sys
import heapq


def solve():
    data = list(map(int, sys.stdin.buffer.read().split()))
    pos = 0

    def next_int():
        nonlocal pos
        val = data[pos]
        pos += 1
        return val

    out = []
    t = next_int()
    for _ in range(t):
        n = next_int()
        m = next_int()  # number of semesters
        k = next_int()  # max courses per semester

        children = [[] for _ in range(n + 1)]
        roots = []
        for course in range(1, n + 1):
            p = next_int()
            if p == 0:
                roots.append(course)
            else:
                children[p].append(course)

        # height[v] = length of the longest chain of courses starting at v
        # (v itself plus its longest line of dependents). Courses on a long
        # chain are urgent: they have to start early to fit everyone in.
        order = []
        stack = list(roots)
        while stack:
            v = stack.pop()
            order.append(v)
            for ch in children[v]:
                stack.append(ch)
        height = [1] * (n + 1)
        for v in reversed(order):
            best = 1
            for ch in children[v]:
                if height[ch] + 1 > best:
                    best = height[ch] + 1
            height[v] = best

        # Go semester by semester. Among the courses whose prerequisite was
        # finished in an earlier semester, always take the ones on the
        # longest remaining chains first (up to k of them).
        available = []
        for r in roots:
            heapq.heappush(available, (-height[r], r))

        taken = 0
        semester = 0
        while available and semester < m:
            semester += 1
            batch = []
            for _ in range(min(k, len(available))):
                _, v = heapq.heappop(available)
                batch.append(v)
            taken += len(batch)
            # Dependents only become available from the NEXT semester on.
            for v in batch:
                for ch in children[v]:
                    heapq.heappush(available, (-height[ch], ch))

        out.append(str(taken))

    sys.stdout.write('\n'.join(out) + '\n')


if __name__ == '__main__':
    solve()
