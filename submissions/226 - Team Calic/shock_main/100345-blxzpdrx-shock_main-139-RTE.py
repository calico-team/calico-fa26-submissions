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
import sys
import numpy as np

def _brute(N, M, eq):
    g = [[0] * M for _ in range(N)]
    for R, C, P in eq:
        pp = P * P + 1
        for r in range(R - P, R + P + 1):
            dr = (r - R) * (r - R)
            row = g[r]
            for c in range(C - P, C + P + 1):
                v = pp - dr - (c - C) * (c - C)
                if v > 0:
                    row[c] = v
    return [' '.join(map(str, row)) for row in g]


def _big(N, M, eq):
    arr = np.array(eq, dtype=np.int64).reshape(-1, 3)
    R = arr[:, 0].copy()
    C = arr[:, 1].copy()
    P = arr[:, 2].copy()
    transpose = N > M
    if transpose:
        N, M = M, N
        R, C = C, R
    P2 = P * P + 1
    maxlen = int(P.max()) * 2 + 1
    K = maxlen.bit_length()          # levels 0 .. K-1
    cols = np.arange(M, dtype=np.int64)
    out = np.zeros((N, M), dtype=np.int64)
    tbl = np.empty((K, M), dtype=np.int32)
    flat = tbl.reshape(-1)

    for r in range(N):
        dy = r - R
        idx = np.nonzero(np.abs(dy) <= P)[0]
        n = idx.size
        if n == 0:
            continue
        d = dy[idx]
        p = P[idx]
        c = C[idx]
        v = p * p - d * d
        h = np.sqrt(v).astype(np.int64)
        h -= (h * h > v)
        h += ((h + 1) * (h + 1) <= v)
        ln = 2 * h + 1
        k = np.frexp(ln.astype(np.float64))[1].astype(np.int64) - 1
        left = c - h
        right = c + h - np.left_shift(1, k) + 1

        tbl.fill(-1)
        pos = np.empty(2 * n, dtype=np.int64)
        pos[0::2] = k * M + left
        pos[1::2] = k * M + right
        # interleaved so that later earthquakes (larger index) win on duplicates
        flat[pos] = np.repeat(idx.astype(np.int32), 2)

        for kk in range(K - 1, 0, -1):
            half = 1 << (kk - 1)
            t = tbl[kk]
            lower = tbl[kk - 1]
            np.maximum(lower, t, out=lower)
            np.maximum(lower[half:], t[:M - half], out=lower[half:])

        i = tbl[0].astype(np.int64)
        valid = i >= 0
        ii = np.where(valid, i, 0)
        val = P2[ii] - (r - R[ii]) ** 2 - (cols - C[ii]) ** 2
        out[r] = np.where(valid, val, 0)

    if transpose:
        out = out.T
    return [' '.join(map(str, row)) for row in out.tolist()]


def solve(N, M, Q, earthquakes):
    if N * M <= 100:
        return _brute(N, M, earthquakes)
    return _big(N, M, earthquakes)

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