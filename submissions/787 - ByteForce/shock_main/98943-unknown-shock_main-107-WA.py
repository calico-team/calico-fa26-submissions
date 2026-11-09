
import sys
from math import isqrt

input = sys.stdin.readline

T = int(input())

for _ in range(T):
    N, M, Q = map(int, input().split())

    earthquakes = [
        tuple(map(int, input().split()))
        for _ in range(Q)
    ]

    # DSU: next unassigned column in each row
    width = M + 1
    parent = [0] * (N * width)

    for r in range(N):
        base = r * width
        for c in range(M + 1):
            parent[base + c] = c

    def find(x):
        root = x
        while parent[root] != root:
            root = parent[root]

        while parent[x] != x:
            nxt = parent[x]
            parent[x] = root
            x = nxt

        return root

    ans = [[0] * M for _ in range(N)]

    # Process earthquakes in reverse order
    for R, C, P in reversed(earthquakes):
        p2 = P * P

        for r in range(R - P, R + P + 1):
            dy = r - R
            dx = isqrt(p2 - dy * dy)

            left = C - dx
            right = C + dx

            base = r * width
            c = find(base + left)

            while c <= right:
                ans[r][c] = p2 - dy * dy - (c - C) ** 2 + 1

                # Mark this column as already assigned
                parent[base + c] = find(base + c + 1)

                c = parent[base + c]

    for row in ans:
        print(*row)
