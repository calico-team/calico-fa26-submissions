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
    from math import isqrt
    g = [[0] * M for _ in range(N)]
    nxt = [list(range(M + 1)) for _ in range(N)]

    def go(r, x):
        arr = nxt[r]
        while arr[x] != x:
            arr[x] = arr[arr[x]]
            x = arr[x]
        return x

    for t in range(Q - 1, -1, -1):
        a, b, p = earthquakes[t]
        pp = p * p
        for i in range(a - p, a + p + 1):
            d = (i - a) * (i - a)
            w = isqrt(pp - d)
            j = go(i, b - w)
            while j <= b + w:
                g[i][j] = pp - d - (j - b) * (j - b) + 1
                nxt[i][j] = go(i, j + 1)
                j = nxt[i][j]
    return g


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
