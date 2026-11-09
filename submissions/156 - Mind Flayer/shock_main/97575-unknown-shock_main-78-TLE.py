try:
    from math import isqrt
except ImportError:  # very old Python
    from math import sqrt
    def isqrt(n):
        r = int(sqrt(n))
        while r * r > n:
            r -= 1
        while (r + 1) * (r + 1) <= n:
            r += 1
        return r

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
    # NOTE: the real input order is "row column power", so in each tuple the
    # first number is the ROW and the second is the COLUMN (see sample 1).
    W = M + 1
    nxt = list(range(N * W))   # nxt[r*W + c] -> next column >= c in row r not yet filled
    ans = [0] * (N * M)
    widths = {}

    # Go backwards: the LAST earthquake that reaches a block decides its reading,
    # so each block is filled the first time a (reversed) earthquake reaches it.
    for i in range(Q - 1, -1, -1):
        R, C, P = earthquakes[i]
        wl = widths.get(P)
        if wl is None:
            wl = [isqrt(P * P - d * d) for d in range(P + 1)]
            widths[P] = wl
        PP = P * P + 1
        for dr in range(-P, P + 1):
            r = R + dr
            w = wl[dr if dr >= 0 else -dr]
            base = r * W
            hi = base + C + w
            x = base + C - w
            rowbase = r * M - base
            drr = dr * dr
            while True:
                root = x
                while nxt[root] != root:
                    root = nxt[root]
                while x != root:
                    nxt[x], x = root, nxt[x]
                if root > hi:
                    break
                dc = root - base - C
                ans[rowbase + root] = PP - drr - dc * dc
                nxt[root] = root + 1
                x = root + 1

    return [ans[r * M:(r + 1) * M] for r in range(N)]


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