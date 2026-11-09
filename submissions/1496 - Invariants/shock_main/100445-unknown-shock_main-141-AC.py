"""
*Return an N by M grid displaying the reading of the block seismometers after all earthquakes occur.
*
*N: number of rows in the grid
*M: number of columns in the grid
*Q: number of earthquakes
*earthquakes: a list of tuples (X, Y, P), where:
*    X: column of the epicenter
*    Y: row of the epicenter
*    P: power of the earthquake
"""
from math import isqrt
def solve(N, M, Q, earthquakes):
    grid = [[0] * M for _ in range(N)]
    free = [(1 << M) - 1] * N
    remaining = N * M
    shapes = {}
    done = set()
    for R, C, P in reversed(earthquakes):
        if not remaining:
            break
        if (R, C, P) in done:
            continue
        done.add((R, C, P))
        shape = shapes.get(P)
        if shape is None:
            shape = []
            for d in range(-P, P + 1):
                w = isqrt(P * P - d * d)
                shape.append((d, P - w, (1 << (2 * w + 1)) - 1))
            shapes[P] = shape
        top = P * P + 1
        left = C - P
        for d, off, span in shape:
            r = R + d
            a = left + off
            seg = free[r] >> a & span
            if not seg:
                continue
            free[r] &= ~(span << a)
            base = top - d * d
            row = grid[r]
            while seg:
                low = seg & -seg
                c = a + low.bit_length() - 1
                row[c] = base - (c - C) * (c - C)
                seg ^= low
                remaining -= 1
    return grid


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