

import sys


def solve():
    
    T = int(input())

    for _ in range(T):
        N, M, Q = map(int, input().split())

        grid = [input().strip() for _ in range(N)]

        cells = N * M
        parent = list(range(2 * cells))
        size = [1] * (2 * cells)

        def find(x):
            while parent[x] != x:
                parent[x] = parent[parent[x]]
                x = parent[x]
            return x

        def union(a, b):
            a = find(a)
            b = find(b)

            if a == b:
                return

            if size[a] < size[b]:
                a, b = b, a

            parent[b] = a
            size[a] += size[b]

        for r in range(N):
            for c in range(M):

                pos = r * M + c
                tile = grid[r][c]

                if tile == ".":
                    union(pos, pos + cells)

                if c > 0:
                    left = grid[r][c - 1]

                    if tile in ".B" and left in ".B":
                        union(pos, pos - 1)

                    if tile in ".R" and left in ".R":
                        union(pos + cells,
                              pos - 1 + cells)

                if r > 0:
                    up = grid[r - 1][c]

                    if tile in ".B" and up in ".B":
                        union(pos, pos - M)

                    if tile in ".R" and up in ".R":
                        union(pos + cells,
                              pos - M + cells)

        for _ in range(Q):

            rs, cs, re, ce = map(int, input().split())

            start = rs * M + cs
            end = re * M + ce

            destination_tile = grid[re][ce]

            if destination_tile == "R":
                end += cells

            if find(start) == find(end):
                print("YES")
            else:
                print("NO")


if __name__ == "__main__":
    solve()
