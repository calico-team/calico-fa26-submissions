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
    W = M + 1
    nxt = list(range(N * W))

    def find(x):
        root = x
        while nxt[root] != root:
            root = nxt[root]
        while nxt[x] != root:
            nxt[x], x = root, nxt[x]
        return root

    for R, C, P in reversed(earthquakes):
        PP = P * P
        w = P
        for dr in range(P + 1):
            while w * w + dr * dr > PP:
                w -= 1
            lo = C - w
            hi = C + w
            rows = (R - dr, R + dr) if dr else (R,)
            for r in rows:
                base = r * W
                row = grid[r]
                c = find(base + lo) - base
                while c <= hi:
                    dc = c - C
                    row[c] = PP - dr * dr - dc * dc + 1
                    nxt[base + c] = base + c + 1
                    c = find(base + c + 1) - base

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