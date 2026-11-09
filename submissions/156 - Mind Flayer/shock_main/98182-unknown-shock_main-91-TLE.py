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

try:
    import numpy as np
except Exception:  # numpy not installed on the judge -> pure Python path is used
    np = None

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

# ---------- pure Python version: go backwards, fill every block once (per-row DSU) ----------
def solve_pure(N, M, Q, earthquakes):
    W = M + 1
    nxt = list(range(N * W))
    ans = [0] * (N * M)
    widths = {}
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


# ---------- numpy version: "range overwrite" with a sparse table, no per-cell loops ----------
def solve_numpy(N, M, Q, earthquakes):
    NM = N * M
    maxP = 0
    for e in earthquakes:
        if e[2] > maxP:
            maxP = e[2]
    K = (2 * maxP + 1).bit_length()          # levels 0 .. K-1
    tab = np.zeros(K * NM, dtype=np.int32)   # tab[k*NM + r*M + c] = latest quake covering [c, c+2^k-1] in row r
    cache = {}
    for t in range(Q):
        R, C, P = earthquakes[t]
        ent = cache.get(P)
        if ent is None:
            dr = np.arange(-P, P + 1, dtype=np.int64)
            w = np.floor(np.sqrt((P * P - dr * dr).astype(np.float64))).astype(np.int64)
            ln = 2 * w + 1
            k = np.frexp(ln.astype(np.float64))[1].astype(np.int64) - 1   # floor(log2(ln))
            pw = np.left_shift(np.int64(1), k)
            rowoff = dr * M
            ent = (k * NM + rowoff - w, k * NM + rowoff + w - pw + 1)
            cache[P] = ent
        off = R * M + C
        tab[ent[0] + off] = t + 1
        tab[ent[1] + off] = t + 1

    # push the table down: level k covers two blocks of level k-1
    for k in range(K - 1, 0, -1):
        half = 1 << (k - 1)
        up = tab[k * NM:(k + 1) * NM].reshape(N, M)
        low = tab[(k - 1) * NM:k * NM].reshape(N, M)
        np.maximum(low, up, out=low)
        if half < M:
            np.maximum(low[:, half:], up[:, :M - half], out=low[:, half:])

    ts = tab[:NM].astype(np.int64)
    Ra = np.zeros(Q + 1, dtype=np.int64)
    Ca = np.zeros(Q + 1, dtype=np.int64)
    Pa = np.zeros(Q + 1, dtype=np.int64)
    arr = np.array(earthquakes, dtype=np.int64).reshape(Q, 3)
    Ra[1:] = arr[:, 0]
    Ca[1:] = arr[:, 1]
    Pa[1:] = arr[:, 2]
    rr = np.repeat(np.arange(N, dtype=np.int64), M)
    cc = np.tile(np.arange(M, dtype=np.int64), N)
    dR = rr - Ra[ts]
    dC = cc - Ca[ts]
    val = Pa[ts] ** 2 - (dR * dR + dC * dC) + 1
    val[ts == 0] = 0
    return val.reshape(N, M).tolist()


def solve(N, M, Q, earthquakes):
    # NOTE: the real input order is "row column power", so in each tuple the
    # first number is the ROW and the second is the COLUMN (see sample 1).
    if np is not None:
        maxP = max(e[2] for e in earthquakes)
        # numpy only pays off when there is a lot of row work
        if Q * (2 * maxP + 1) >= 20000:
            try:
                return solve_numpy(N, M, Q, earthquakes)
            except Exception:
                pass
    return solve_pure(N, M, Q, earthquakes)


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