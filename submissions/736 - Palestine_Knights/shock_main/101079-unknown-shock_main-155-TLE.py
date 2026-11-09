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

    # Next unassigned column in each row
    parent = [list(range(M + 1)) for _ in range(N)]

    def find(row_parent, x):
        while row_parent[x] != x:
            row_parent[x] = row_parent[row_parent[x]]
            x = row_parent[x]
        return x

    # Process earthquakes in reverse order
    for r, c, p in reversed(earthquakes):
        p2 = p * p

        for dr in range(-p, p + 1):
            row = r + dr
            remaining = p2 - dr * dr
            width = isqrt(remaining)

            left = c - width
            right = c + width

            row_parent = parent[row]
            row_values = grid[row]
            base = remaining + 1

            col = find(row_parent, left)

            while col <= right:
                dc = col - c
                row_values[col] = base - dc * dc

                row_parent[col] = find(row_parent, col + 1)

                col = row_parent[col]

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