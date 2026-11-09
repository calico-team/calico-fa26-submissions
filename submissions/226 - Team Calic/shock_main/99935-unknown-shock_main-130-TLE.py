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
    W = M + 1
    nxt = list(range(N * W))        # nxt[r*W + c] = next unpainted column >= c in row r (c = M is sentinel)
    res = [0] * (N * M)
    cache = {}

    def widths(P):
        # w[dy] = floor(sqrt(P^2 - dy^2)) for dy = 0..P
        w = cache.get(P)
        if w is None:
            w = []
            cur = P
            pp = P * P
            for dy in range(P + 1):
                while cur * cur + dy * dy > pp:
                    cur -= 1
                w.append(cur)
            cache[P] = w
        return w

    for i in range(Q - 1, -1, -1):
        R, C, P = earthquakes[i]
        w = widths(P)
        top = P * P + 1
        for dy in range(-P, P + 1):
            r = R + dy
            half = w[dy if dy >= 0 else -dy]
            lo = C - half
            hi = C + half
            off = r * W
            roff = r * M

            x = off + lo
            root = x
            while nxt[root] != root:
                root = nxt[root]
            while nxt[x] != root:
                nxt[x], x = root, nxt[x]
            c = root - off
            base = top - dy * dy
            while c <= hi:
                d = c - C
                res[roff + c] = base - d * d
                nxt[off + c] = off + c + 1

                x = off + c + 1
                root = x
                while nxt[root] != root:
                    root = nxt[root]
                while nxt[x] != root:
                    nxt[x], x = root, nxt[x]
                c = root - off

    return [res[r * M:(r + 1) * M] for r in range(N)]

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