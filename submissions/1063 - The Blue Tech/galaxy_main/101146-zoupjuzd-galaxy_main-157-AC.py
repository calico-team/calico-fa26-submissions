import sys
from collections import deque

input = sys.stdin.readline


def can_stand(tile, mode):
    if tile == ".":
        return True
    if mode == 0:
        return tile == "B"
    return tile == "R"


def bfs(grid, n, m, group, mode, r, c, label):
    queue = deque()
    group[mode][r][c] = label
    queue.append((mode, r, c))

    while queue:
        mode, r, c = queue.popleft()

        if grid[r][c] == ".":
            other = 1 - mode
            if group[other][r][c] == -1:
                group[other][r][c] = label
                queue.append((other, r, c))

        for dr, dc in ((1, 0), (-1, 0), (0, 1), (0, -1)):
            nr = r + dr
            nc = c + dc
            if 0 <= nr < n and 0 <= nc < m:
                if group[mode][nr][nc] == -1 and can_stand(grid[nr][nc], mode):
                    group[mode][nr][nc] = label
                    queue.append((mode, nr, nc))


def find_groups(grid, n, m):
    group = [[[-1] * m for _ in range(n)] for _ in range(2)]
    label = 0

    for mode in range(2):
        for r in range(n):
            for c in range(m):
                if group[mode][r][c] == -1 and can_stand(grid[r][c], mode):
                    bfs(grid, n, m, group, mode, r, c, label)
                    label = label + 1

    return group


def answer_query(group, rs, cs, re, ce):
    start = group[0][rs][cs]

    if group[0][re][ce] == start or group[1][re][ce] == start:
        return "YES"
    return "NO"


def solve_case(output):
    n, m, q = map(int, input().split())

    grid = []
    for i in range(n):
        grid.append(input().strip())

    group = find_groups(grid, n, m)

    for i in range(q):
        rs, cs, re, ce = map(int, input().split())
        output.append(answer_query(group, rs, cs, re, ce))


def main():
    t = int(input())
    output = []

    for i in range(t):
        solve_case(output)

    print("\n".join(output))


main()