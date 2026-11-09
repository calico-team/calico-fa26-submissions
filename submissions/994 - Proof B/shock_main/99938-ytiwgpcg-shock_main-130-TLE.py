import math

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
    grid = [[0] * M for _ in range(N)]

    while earthquakes:
        eqx, eqy, eqp = earthquakes.pop()
        d = math.ceil(eqp ** 0.5)
        for x in range(min(eqx - d, 0), max(eqx + d, N-1) + 1):
            for y in range(min(eqy - d, 0), max(eqy + d, M-1) + 1):
                if grid[x][y] == 0:
                    grid[x][y] = max(0, eqp ** 2 - (x - eqx) ** 2 - (y - eqy) ** 2 + 1)

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