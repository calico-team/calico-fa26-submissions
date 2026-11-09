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
    import math

    ans = [[0] * M for _ in range(N)]

    # DSU: next unassigned column in each row
    parent = [list(range(M + 1)) for _ in range(N)]

    def find(r, x):
        while parent[r][x] != x:
            parent[r][x] = parent[r][parent[r][x]]
            x = parent[r][x]
        return x

    # Process earthquakes in reverse chronological order
    for X, Y, P in reversed(earthquakes):
        R = X
        C = Y

        p2 = P * P

        for r in range(R - P, R + P + 1):
            dy = r - R
            dx = math.isqrt(p2 - dy * dy)

            left = C - dx
            right = C + dx

            c = find(r, left)

            while c <= right:
                ans[r][c] = p2 - dy * dy - (c - C) ** 2 + 1

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