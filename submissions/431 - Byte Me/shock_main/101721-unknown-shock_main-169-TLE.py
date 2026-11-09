import sys
from math import isqrt

input = sys.stdin.buffer.readline

def find(parent, x):
    while parent[x] != x:
        parent[x] = parent[parent[x]]
        x = parent[x]
    return x

T = int(input())
answer = []
widths = {}

for _ in range(T):
    N, M, Q = map(int, input().split())
    earthquakes = [tuple(map(int, input().split())) for _ in range(Q)]

    size = N * M
    grid = [0] * size
    parent = list(range(size + 1))
    row_parent = list(range(N + 1))
    remaining = [M] * N

    for R, C, P in reversed(earthquakes):
        if P not in widths:
            p2 = P * P
            widths[P] = [isqrt(p2 - d * d) for d in range(P + 1)]

        w = widths[P]
        power = P * P
        r = find(row_parent, R - P)
        last = R + P

        while r <= last:
            d = abs(r - R)
            width = w[d]
            base = r * M
            end = base + C + width
            x = find(parent, base + C - width)

            while x <= end:
                dx = x - base - C
                grid[x] = power - d * d - dx * dx + 1
                parent[x] = find(parent, x + 1)
                remaining[r] -= 1
                x = parent[x]

            if remaining[r] == 0:
                row_parent[r] = find(row_parent, r + 1)
            r = find(row_parent, r + 1)

    for r in range(N):
        start = r * M
        answer.append(" ".join(map(str, grid[start:start + M])))

sys.stdout.write("\n".join(answer))