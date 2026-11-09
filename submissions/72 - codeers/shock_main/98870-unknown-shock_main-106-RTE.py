
from math import isqrt
from array import array

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
    answer = [[0] * M for _ in range(N)]

    # DSU: skip columns that have already been assigned.
    parent = array('i', range(N * (M + 1)))

    def find(x):
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x

    # Process earthquakes in reverse chronological order.
    for X, Y, P in reversed(earthquakes):

        p2 = P * P

        # Find all rows affected by this earthquake.
        for r in range(Y - P, Y + P + 1):

            dy = r - Y
            dx = isqrt(p2 - dy * dy)

            left = X - dx
            right = X + dx

            offset = r * (M + 1)

            # Find the first unassigned column.
            c = find(offset + left)

            while c < offset + right + 1:

                col = c - offset

                # Calculate the shock level.
                dist2 = dy * dy + (col - X) ** 2
                answer[r][col] = p2 - dist2 + 1

                # Mark this cell as assigned.
                parent[c] = find(c + 1)

                # Find the next unassigned cell.
                c = find(c)

    return answer


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
