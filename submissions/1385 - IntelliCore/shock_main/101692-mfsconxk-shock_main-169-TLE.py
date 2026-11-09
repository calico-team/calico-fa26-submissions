from math import isqrt
from array import array

def find(parent, x):
    root = x

    while parent[root] != root:
        root = parent[root]

    while parent[x] != x:
        next_node = parent[x]
        parent[x] = root
        x = next_node

    return root

T = int(input())

for i in range(T):
    n, m, q = map(int, input().split())

    earthquakes = []

    for i in range(q):
        r, c, p = map(int, input().split())
        earthquakes.append((r, c, p))

    answer = array('i', [0]) * (n * m)

    parent = array('i', range(n * (m + 1)))

    for r0, c0, p in reversed(earthquakes):

        for r in range(r0 - p, r0 + p + 1):
            dy = r - r0

            d = isqrt(p * p - dy * dy)

            left = c0 - d
            right = c0 + d

            base = r * (m + 1)

            pos = find(parent, base + left)
            end = base + right

            while pos <= end:
                c = pos - base

                value = p * p - dy * dy - (c - c0) ** 2 + 1

                answer[r * m + c] = value

                parent[pos] = find(parent, pos + 1)
                pos = parent[pos]

    for r in range(n):
        row = answer[r * m:(r + 1) * m]
        print(*row)