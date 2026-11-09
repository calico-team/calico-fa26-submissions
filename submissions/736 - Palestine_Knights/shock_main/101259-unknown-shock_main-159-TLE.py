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
from math import isqrt

def solve(N, M, Q, earthquakes):
    grid = [[0] * M for _ in range(N)]
    skip = [list(range(M + 1)) for _ in range(N)]

    def next_free(row_skip, y):
        while row_skip[y] != y:
            row_skip[y] = row_skip[row_skip[y]]
            y = row_skip[y]
        return y

    for R, C, P in reversed(earthquakes):
        for x in range(max(0, R - P), min(N, R + P + 1)):
            dx2 = (x - R) ** 2
            w = isqrt(P * P - dx2)
            left, right = max(0, C - w), min(M - 1, C + w)

            y = next_free(skip[x], left)
            while y <= right:
                grid[x][y] = P * P + 1 - dx2 - (y - C) ** 2
                skip[x][y] = y + 1
                y = next_free(skip[x], y)
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