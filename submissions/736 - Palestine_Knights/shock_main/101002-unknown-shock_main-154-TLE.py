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
    grid = [[0] * M for _ in range(N)]

    for r, c, p in earthquakes:
        p2 = p * p

        for dr in range(-p, p + 1):
            row = r + dr

            remaining = p2 - dr * dr
            width = isqrt(remaining)

            left = c - width
            right = c + width

            current_row = grid[row]
            base = remaining + 1

            for col in range(left, right + 1):
                dc = col - c
                current_row[col] = base - dc * dc

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