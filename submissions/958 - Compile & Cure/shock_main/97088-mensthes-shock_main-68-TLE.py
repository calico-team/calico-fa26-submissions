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
    nxt = [list(range(M + 1)) for _ in range(N)]
    left_in_row = [M] * N

    for i in range(Q - 1, -1, -1):
        r0, c0, p = earthquakes[i]
        pp = p * p
        for dy in range(-p, p + 1):
            r = r0 + dy
            if left_in_row[r] == 0:
                continue
            rest = pp - dy * dy
            w = isqrt(rest)
            right = c0 + w
            jump = nxt[r]
            row = grid[r]

            c = c0 - w
            start = c
            while jump[c] != c:
                c = jump[c]
            while jump[start] != c:
                jump[start], start = c, jump[start]

            while c <= right:
                dx = c - c0
                row[c] = rest - dx * dx + 1
                left_in_row[r] -= 1
                jump[c] = c + 1
                d = c + 1
                while jump[d] != d:
                    d = jump[d]
                jump[c] = d
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