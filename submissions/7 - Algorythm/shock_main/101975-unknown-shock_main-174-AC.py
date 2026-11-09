
import re
from math import isqrt

"""
Return an N by M grid displaying the reading of the block seismometers after all earthquakes occur.

N: number of rows in the grid
M: number of columns in the grid
Q: number of earthquakes
earthquakes: a list of tuples (X, Y, P), where:
    X: column of the epicenter
    Y: row of the epicenter
    P: power of the earthquake
"""

def solve_small(N, M, Q, earthquakes):
    W = M + 1
    parent = list(range(N * W))
    grid = [[0] * M for _ in range(N)]

    for R, C, P in reversed(earthquakes):
        pp = P * P

        for r in range(R - P, R + P + 1):
            dr = r - R
            rem = pp - dr * dr
            w = isqrt(rem)
            base = r * W
            hi = base + C + w
            row = grid[r]
            j = base + C - w

            while parent[j] != j:
                parent[j] = parent[parent[j]]
                j = parent[j]

            while j <= hi:
                dc = j - base - C
                row[j - base] = rem + 1 - dc * dc
                parent[j] = j + 1
                j += 1

                while parent[j] != j:
                    parent[j] = parent[parent[j]]
                    j = parent[j]

    return grid


_pat = re.compile(rb'[^\x00]{1,8}')


def solve_big(N, M, Q, earthquakes):
    # Use big-integer bitmasks (one bit per cell, row stride S) so a whole
    # earthquake disk is handled with a few big-int operations.
    trans = M < N

    if trans:
        N, M = M, N
        earthquakes = [(c, r, p) for (r, c, p) in earthquakes]

    S = (M + 7) // 8 * 8
    S8 = S // 8
    unfilled = (1 << (N * S)) - 1
    out = [0] * (N * S)
    shapes = {}
    from_bytes = int.from_bytes
    find = _pat.finditer

    for R, C, P in reversed(earthquakes):
        if not unfilled:
            break

        sh = shapes.get(P)

        if sh is None:
            pp = P * P
            rows = []

            for j in range(2 * P + 1):
                dr = j - P
                w = isqrt(pp - dr * dr)
                rows.append((((1 << (2 * w + 1)) - 1) << (P - w)).to_bytes(S8, 'little'))

            sh = (from_bytes(b''.join(rows), 'little'), (2 * P + 1) * S8)
            shapes[P] = sh

        shape, nb = sh
        shift = (R - P) * S + (C - P)
        new = (shape << shift) & unfilled

        if not new:
            continue

        unfilled ^= new
        data = (new >> shift).to_bytes(nb, 'little')
        pp1 = P * P + 1

        for m in find(data):
            v = from_bytes(m.group(), 'little')
            base = m.start() * 8

            while v:
                low = v & -v
                v ^= low
                idx = base + low.bit_length() - 1
                lr = idx // S
                dr = lr - P
                dc = idx - lr * S - P
                out[shift + idx] = pp1 - dr * dr - dc * dc

    grid = [out[r * S: r * S + M] for r in range(N)]

    if trans:
        grid = [list(x) for x in zip(*grid)]

    return grid


def solve(N, M, Q, earthquakes):
    visits = 0

    for (_, _, P) in earthquakes:
        visits += 2 * P + 1

    # rough cost model (microseconds): per-row path vs big-int path
    if visits < 3000 or visits * 0.8 < Q * N * M * 0.00012:
        return solve_small(N, M, Q, earthquakes)

    return solve_big(N, M, Q, earthquakes)


def main():
    T = int(input())

    for _ in range(T):
        N, M, Q = map(int, input().split())
        earthquakes = []

        for i in range(Q):
            X, Y, P = map(int, input().split())
            earthquakes.append((X, Y, P))

        answer = solve(N, M, Q, earthquakes)

        for row in answer:
            print(' '.join(map(str, row)))


if __name__ == '__main__':
    main()
