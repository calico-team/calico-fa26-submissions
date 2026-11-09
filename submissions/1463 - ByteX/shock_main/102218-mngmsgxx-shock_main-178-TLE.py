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
    # nxt[r][c] = smallest unfilled column >= c in row r (M means none left)
    nxt = [list(range(M + 1)) for _ in range(N)]
    remaining = N * M
    for R, C, P in reversed(earthquakes):      # the last earthquake that hits a cell wins
        if remaining == 0:
            break
        p2 = P * P
        r0 = max(0, R - P)
        r1 = min(N - 1, R + P)
        for r in range(r0, r1 + 1):
            dx = r - R
            rem = p2 - dx * dx
            w = isqrt(rem)                     # half-width of the affected columns in this row
            lo = max(0, C - w)
            hi = min(M - 1, C + w)
            if lo > hi:
                continue
            nx = nxt[r]
            row = grid[r]
            c = lo
            while nx[c] != c:                  # find first unfilled column >= lo
                nx[c] = nx[nx[c]]
                c = nx[c]
            while c <= hi:
                dy = c - C
                row[c] = rem - dy * dy + 1     # P^2 - dist^2 + 1
                remaining -= 1
                nx[c] = c + 1
                d = c + 1
                while nx[d] != d:
                    nx[d] = nx[nx[d]]
                    d = nx[d]
                c = d
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