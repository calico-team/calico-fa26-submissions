from math import isqrt

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
def solve(N, M, Q, earthquakes):
    W = M + 1
    # parent[i] = next unfilled cell at or after i within its row (column M is a sentinel)
    parent = list(range(N * W))
    grid = [[0] * M for _ in range(N)]

    # NOTE: per the input format, the first value is the row, the second the column.
    for R, C, P in reversed(earthquakes):
        pp = P * P
        for r in range(R - P, R + P + 1):
            dr = r - R
            rem = pp - dr * dr          # shock at column C is rem + 1
            w = isqrt(rem)
            base = r * W
            hi = base + C + w
            row = grid[r]

            # find first unfilled cell >= base + C - w
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