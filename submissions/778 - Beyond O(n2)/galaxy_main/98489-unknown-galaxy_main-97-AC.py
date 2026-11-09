import sys
from collections import deque

input = sys.stdin.readline

t = int(input())
answers = []

for _ in range(t):
    n, m, q = map(int, input().split())
    grid = [input().strip() for _ in range(n)]

    # Mode 0 is blue; mode 1 is red.
    comp = [-1] * (n * m * 2)
    comp_id = 0
    dr = [-1, 1, 0, 0]
    dc = [0, 0, -1, 1]

    for state in range(n * m * 2):
        cell = state // 2
        mode = state % 2
        r = cell // m
        c = cell % m
        tile = grid[r][c]

        if tile == "R" and mode == 0:
            continue
        if tile == "B" and mode == 1:
            continue
        if comp[state] != -1:
            continue

        comp[state] = comp_id
        queue = deque([state])

        while queue:
            current = queue.popleft()
            cell = current // 2
            mode = current % 2
            r = cell // m
            c = cell % m

            if grid[r][c] == ".":
                other = current ^ 1
                if comp[other] == -1:
                    comp[other] = comp_id
                    queue.append(other)

            for d in range(4):
                nr = r + dr[d]
                nc = c + dc[d]

                if nr < 0 or nr >= n or nc < 0 or nc >= m:
                    continue

                tile = grid[nr][nc]
                active = (
                    tile == "."
                    or (tile == "B" and mode == 0)
                    or (tile == "R" and mode == 1)
                )

                if active:
                    next_state = (nr * m + nc) * 2 + mode
                    if comp[next_state] == -1:
                        comp[next_state] = comp_id
                        queue.append(next_state)

        comp_id += 1

    for _ in range(q):
        sr, sc, er, ec = map(int, input().split())

        start_state = (sr * m + sc) * 2  # Starts in blue mode
        destination = (er * m + ec) * 2
        tile = grid[er][ec]

        possible = False

        for mode in range(2):
            active = (
                tile == "."
                or (tile == "B" and mode == 0)
                or (tile == "R" and mode == 1)
            )

            if active and comp[destination + mode] == comp[start_state]:
                possible = True

        if possible:
            answers.append("YES")
        else:
            answers.append("NO")

print("\n".join(answers))