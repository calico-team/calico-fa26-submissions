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
    filled = [0] * N
    remaining = N * M
    cache = {}

    for R, C, P in reversed(earthquakes):
        if remaining == 0:
            break

        ws = cache.get(P)
        if ws is None:
            PP0 = P * P
            ws = []
            w = P
            for dr in range(P + 1):
                while w * w + dr * dr > PP0:
                    w -= 1
                ws.append(w)
            cache[P] = ws

        PP = P * P + 1
        for dr in range(P + 1):
            w = ws[dr]
            lo = C - w
            hi = C + w
            val = PP - dr * dr
            for r in ((R - dr, R + dr) if dr else (R,)):
                if filled[r] == M:
                    continue
                base = r * W
                end = base + hi

                x = base + lo
                root = x
                while nxt[root] != root:
                    root = nxt[root]
                while nxt[x] != root:
                    nxt[x], x = root, nxt[x]

                if root > end:
                    continue

                row = grid[r]
                cnt = 0
                while root <= end:
                    d = root - base - C
                    row[root - base] = val - d * d
                    nxt[root] = root + 1
                    cnt += 1
                    x = root + 1
                    root = x
                    while nxt[root] != root:
                        root = nxt[root]
                    while nxt[x] != root:
                        nxt[x], x = root, nxt[x]
                filled[r] += cnt
                remaining -= cnt


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