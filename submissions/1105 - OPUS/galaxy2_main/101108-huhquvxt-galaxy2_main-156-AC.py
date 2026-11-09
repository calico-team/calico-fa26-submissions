import sys
from collections import deque

def solve():
    input = sys.stdin.buffer.readline
    cases = int(input())
    out = []

    for _ in range(cases):
        n, m, q = map(int, input().split())
        grid = [input().strip() for _ in range(n)]

        size = 2 * n * m
        adj = [[] for _ in range(size)]
        enabled = bytearray(size)

        for col in range(m):
            for row in range(n):
                idx = 2 * (col * n + row)
                cell = grid[row][col]

                enabled[idx] = cell != 82
                enabled[idx + 1] = cell != 66

                if cell == 46:
                    adj[idx].append(idx + 1)
                    adj[idx + 1].append(idx)

                for mode in (0, 1):
                    u = idx + mode

                    if not enabled[u]:
                        continue

                    if row > 0 and enabled[u - 2]:
                        v = u - 2
                        adj[u].append(v)
                        adj[v].append(u)

                    if col > 0 and enabled[u - 2 * n]:
                        v = u - 2 * n
                        adj[u].append(v)
                        adj[v].append(u)

        source = [0] * q
        target = [None] * q
        cols = [None] * q
        limit = [0] * q
        answer = bytearray(q)
        pending = []

        for i in range(q):
            sr, sc, tr, tc, k = map(int, input().split())

            a = 2 * (sc * n + sr)
            b = 2 * (tc * n + tr)

            source[i] = a
            target[i] = (
                b if enabled[b] else -1,
                b + 1 if enabled[b + 1] else -1
            )
            cols[i] = (sc, tc)
            limit[i] = k

            if sr == tr and sc == tc:
                answer[i] = 1
            elif abs(sr - tr) + abs(sc - tc) <= k:
                pending.append(i)

        seen = [0] * size
        dist = [0] * size
        col_of = [i // (2 * n) for i in range(size)]
        stamp = 0

        jobs = [(0, m - 1, pending)]

        while jobs:
            left, right, ids = jobs.pop()

            if not ids:
                continue

            mid = (left + right) // 2

            for row in range(n):
                for mode in (0, 1):
                    start = 2 * (mid * n + row) + mode

                    if not enabled[start]:
                        continue

                    stamp += 1
                    bfs = deque([start])
                    seen[start] = stamp
                    dist[start] = 0

                    while bfs:
                        u = bfs.popleft()
                        nd = dist[u] + 1

                        for v in adj[u]:
                            if seen[v] != stamp and left <= col_of[v] <= right:
                                seen[v] = stamp
                                dist[v] = nd
                                bfs.append(v)

                    for i in ids:
                        a = source[i]

                        if answer[i] or seen[a] != stamp:
                            continue

                        steps = dist[a]
                        b0, b1 = target[i]

                        if ((b0 >= 0 and seen[b0] == stamp and
                             steps + dist[b0] <= limit[i]) or
                            (b1 >= 0 and seen[b1] == stamp and
                             steps + dist[b1] <= limit[i])):
                            answer[i] = 1

            if left == right:
                continue

            left_ids = []
            right_ids = []

            for i in ids:
                if answer[i]:
                    continue

                sc, tc = cols[i]

                if sc < mid and tc < mid:
                    left_ids.append(i)
                elif sc > mid and tc > mid:
                    right_ids.append(i)

            if left_ids:
                jobs.append((left, mid - 1, left_ids))

            if right_ids:
                jobs.append((mid + 1, right, right_ids))

        out.extend('YES' if v else 'NO' for v in answer)

    sys.stdout.write('\n'.join(out))

solve()
