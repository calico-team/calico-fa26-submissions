
import sys
from collections import deque


def solve():
    input = sys.stdin.buffer.readline
    T = int(input())

    output = []

    for _ in range(T):
        N, M, Q = map(int, input().split())
        grid = [input().strip().decode() for _ in range(N)]

        queries = []
        grouped = {}

        for qi in range(Q):
            sr, sc, er, ec, k = map(int, input().split())
            start = sr * M + sc
            queries.append((er * M + ec, k))

            if start not in grouped:
                grouped[start] = []
            grouped[start].append((qi, er * M + ec, k))

        size = N * M
        total = 2 * size

        # State 0 = blue mode, state 1 = red mode.
        # A normal tile is active in both modes.
        active = [bytearray(size), bytearray(size)]

        for r in range(N):
            for c in range(M):
                ch = grid[r][c]
                pos = r * M + c

                if ch == '.' or ch == 'B':
                    active[0][pos] = 1
                if ch == '.' or ch == 'R':
                    active[1][pos] = 1

        answers = ['NO'] * Q

        for start, items in grouped.items():
            max_k = max(k for _, _, k in items)

            # Starting tile is normal, and initial mode is blue.
            source = start
            dist = [-1] * total
            dist[source] = 0

            queue = deque([source])

            # Group queries by destination to answer after BFS.
            targets = {}
            for qi, target, k in items:
                if target not in targets:
                    targets[target] = []
                targets[target].append((qi, k))

            while queue:
                u = queue.popleft()
                d = dist[u]

                if d == max_k:
                    continue

                mode = u // size
                pos = u % size
                r, c = divmod(pos, M)
                nd = d + 1

                # Spin on a normal tile.
                if grid[r][c] == '.':
                    v = (1 - mode) * size + pos
                    if dist[v] == -1:
                        dist[v] = nd
                        queue.append(v)

                # Move to adjacent cells in the same mode.
                if r > 0:
                    vpos = pos - M
                    if active[mode][vpos]:
                        v = mode * size + vpos
                        if dist[v] == -1:
                            dist[v] = nd
                            queue.append(v)

                if r + 1 < N:
                    vpos = pos + M
                    if active[mode][vpos]:
                        v = mode * size + vpos
                        if dist[v] == -1:
                            dist[v] = nd
                            queue.append(v)

                if c > 0:
                    vpos = pos - 1
                    if active[mode][vpos]:
                        v = mode * size + vpos
                        if dist[v] == -1:
                            dist[v] = nd
                            queue.append(v)

                if c + 1 < M:
                    vpos = pos + 1
                    if active[mode][vpos]:
                        v = mode * size + vpos
                        if dist[v] == -1:
                            dist[v] = nd
                            queue.append(v)

            for target, requests in targets.items():
                best = -1

                if active[0][target]:
                    best = dist[target]

                if active[1][target]:
                    other = dist[size + target]
                    if other != -1 and (best == -1 or other < best):
                        best = other

                if best != -1:
                    for qi, k in requests:
                        if best <= k:
                            answers[qi] = 'YES'

        output.extend(answers)

    sys.stdout.write('\n'.join(output))


if __name__ == "__main__":
    solve()
