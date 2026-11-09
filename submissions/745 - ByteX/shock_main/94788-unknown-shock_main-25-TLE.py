
import sys
from math import isqrt

input = sys.stdin.readline

t = int(input())

for _ in range(t):
    n, m, q = map(int, input().split())

    earthquakes = []
    for _ in range(q):
        r, c, p = map(int, input().split())
        earthquakes.append((r, c, p))

    ans = [[0] * m for _ in range(n)]

    parent = [list(range(m + 1)) for _ in range(n)]

    def find(r, x):
        while parent[r][x] != x:
            parent[r][x] = parent[r][parent[r][x]]
            x = parent[r][x]
        return x

    for R, C, P in reversed(earthquakes):
        p2 = P * P

        for r in range(R - P, R + P + 1):
            dr = r - R
            dx = isqrt(p2 - dr * dr)

            l = C - dx
            rr = C + dx

            c = find(r, l)

            while c <= rr:
                dc = c - C
                ans[r][c] = p2 - dr * dr - dc * dc + 1

                parent[r][c] = find(r, c + 1)
                c = find(r, c)

    for row in ans:
        print(*row)
