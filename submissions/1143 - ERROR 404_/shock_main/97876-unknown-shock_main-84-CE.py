import sys
import math

def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return

    idx = 0
    t = data[idx]
    idx += 1
    out_lines = []

    for _ in range(t):
        n = data[idx]
        m = data[idx + 1]
        q = data[idx + 2]
        idx += 3

        quakes = []
        for _ in range(q):
            r = data[idx]
            c = data[idx + 1]
            p = data[idx + 2]
            idx += 3
            quakes.append((r, c, p))

        ans = [[0] * m for _ in range(n)]

        # parent[r][c] = next candidate >= c in row r, m = sentinel
        parent = [list(range(m + 1)) for _ in range(n)]
        # row_parent[r] = next row >= r that is not completely filled
        row_parent = list(range(n + 1))
        row_rem = [m] * n

        def find_row(x: int) -> int:
            # iterative path compression
            while row_parent[x] != x:
                row_parent[x] = row_parent[row_parent[x]]
                x = row_parent[x]
            return x

        def find_col(par, x: int) -> int:
            while par[x] != x:
                par[x] = par[par[x]]
                x = par[x]
            return x

        filled_total = 0
        total = n * m

        # Last earthquake covering a cell wins -> go backwards.
        for R, C, P in reversed(quakes):
            if filled_total >= total:
                break

            p2 = P * P
            r1 = R - P
            r2 = R + P
            if r1 < 0:
                r1 = 0
            if r2 >= n:
                r2 = n - 1

            r = find_row(r1)
            while r <= r2:
                dx = r - R
                rem = p2 - dx * dx
                d = math.isqrt(rem)  # exact, no float error
                L = C - d
                Rr = C + d
                if L < 0:
                   