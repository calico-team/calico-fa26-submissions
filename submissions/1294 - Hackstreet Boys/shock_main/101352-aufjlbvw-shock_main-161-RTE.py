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

    parent = [
        array('i', range(M + 1))
        for _ in range(N)
    ]

    def find(row, x):
        p = parent[row]
        root = x

        while p[root] != root:
            root = p[root]

        while p[x] != x:
            nxt = p[x]
            p[x] = root
            x = nxt

        return root

    for X, Y, P in reversed(earthquakes):
        p2 = P * P

        for r in range(Y - P, Y + P + 1):
            dy = r - Y
            dx = isqrt(p2 - dy * dy)

            left = X - dx
            right = X + dx

            c = find(r, left)

            while c <= right:
                ans[r][c] = p2 - dy * dy - (c - X) ** 2 + 1

                parent[r][c] = find(r, c + 1)
                c = parent[r][c]

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