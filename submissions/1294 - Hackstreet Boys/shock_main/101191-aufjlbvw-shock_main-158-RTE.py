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
    from array import array
    from math import isqrt

    ans = [[0] * M for _ in range(N)]

    # Flattened DSU: each row has M + 1 positions.
    W = M + 1
    parent = array('i', range(N * W))

    def find(x):
        root = x

        while parent[root] != root:
            root = parent[root]

        while parent[x] != x:
            nxt = parent[x]
            parent[x] = root
            x = nxt

        return root

    # Process earthquakes in reverse order.
    for X, Y, P in reversed(earthquakes):

        p2 = P * P

        # Y is the row, X is the column.
        for r in range(Y - P, Y + P + 1):

            dy = r - Y
            dx = isqrt(p2 - dy * dy)

            left = X - dx
            right = X + dx

            base = r * W

            c = find(base + left)

            while c < base + W and c - base <= right:

                col = c - base

                ans[r][col] = (
                    p2 - dy * dy - (col - X) ** 2 + 1
                )

                # Remove this cell from future consideration.
                parent[c] = find(c + 1)

                c = parent[c]

    return ans


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