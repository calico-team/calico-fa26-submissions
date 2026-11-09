import sys
from math import isqrt

input = sys.stdin.readline

T = int(input())
answers = []

for _ in range(T):
    n, m, q = map(int, input().split())
    earthquakes = []

    for _ in range(q):
        r, c, p = map(int, input().split())
        earthquakes.append((r, c, p))

    result = [[0] * m for _ in range(n)]

    # For each row, parent[x] points to the next unassigned column.
    parent = [list(range(m + 1)) for _ in range(n)]

    def find(row, x):
        while parent[row][x] != x:
            parent[row][x] = parent[row][parent[row][x]]
            x = parent[row][x]
        return x

    # Process backwards so each block receives its latest earthquake.
    for r0, c0, p in reversed(earthquakes):
        p_squared = p * p
        top = max(0, r0 - p)
        bottom = min(n - 1, r0 + p)

        for r in range(top, bottom + 1):
            dy = r - r0
            max_dx = isqrt(p_squared - dy * dy)
            left = max(0, c0 - max_dx)
            right = min(m - 1, c0 + max_dx)

            c = find(r, left)
            while c <= right:
                dx = c - c0
                result[r][c] = p_squared - dy * dy - dx * dx + 1
                parent[r][c] = find(r, c + 1)
                c = find(r, c)

    for row in result:
        answers.append(" ".join(map(str, row)))

sys.stdout.write("\n".join(answers))