from math import isqrt
import numpy as np

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
def solve_small(N, M, Q, earthquakes):
    W = M + 1
    parent = list(range(N * W))
    grid = [[0] * M for _ in range(N)]
    for R, C, P in reversed(earthquakes):
        pp = P * P
        for r in range(R - P, R + P + 1):
            dr = r - R
            rem = pp - dr * dr
            w = isqrt(rem)
            base = r * W
            hi = base + C + w
            row = grid[r]
            j = base + C - w
            while parent[j] != j:
                parent[j] = parent[parent[j]]
                j = parent[j]
            while j <= hi:
                dc = j - base - C
                row[j - base] = rem + 1 - dc * dc
                parent[j] = j + 1
                j += 1
                while parent[j] != j:
                    parent[j] = parent[parent[j]]
                    j = parent[j]
    return grid


def solve_big(N, M, Q, earthquakes):
    NM = N * M
    K = M.bit_length()
    table = np.zeros(K * NM, dtype=np.int32)
    arr = np.array(earthquakes, dtype=np.int64)
    R = arr[:, 0]
    C = arr[:, 1]
    P = arr[:, 2]
    counts = 2 * P + 1
    LIMIT = 1_000_000

    start = 0
    while start < Q:
        # build a chunk of earthquakes with bounded total row count
        end = start
        tot = 0
        while end < Q and (tot + counts[end] <= LIMIT or end == start):
            tot += int(counts[end])
            end += 1
        cnt = counts[start:end]
        Rc, Cc, Pc = R[start:end], C[start:end], P[start:end]
        n = end - start
        idx = np.repeat(np.arange(n), cnt)
        starts = np.cumsum(cnt) - cnt
        offs = np.arange(tot, dtype=np.int64) - np.repeat(starts, cnt)
        Pi = Pc[idx]
        dr = offs - Pi
        r = Rc[idx] + dr
        rem = Pi * Pi - dr * dr
        w = np.sqrt(rem.astype(np.float64)).astype(np.int64)
        w -= (w * w > rem)
        w += ((w + 1) * (w + 1) <= rem)
        l = Cc[idx] - w
        length = 2 * w + 1
        k = (np.frexp(length.astype(np.float64))[1] - 1).astype(np.int64)
        p2 = l + length - (np.int64(1) << k)
        base = k * NM + r * M
        pos = np.stack([base + l, base + p2], axis=1).ravel()
        times = np.repeat((idx + start + 1).astype(np.int32), 2)
        table[pos] = times  # later (higher time) entries overwrite earlier ones
        start = end

    t = table.reshape(K, NM)
    for k in range(K - 1, 0, -1):
        half = 1 << (k - 1)
        a = t[k]
        lower = t[k - 1]
        np.maximum(lower, a, out=lower)
        np.maximum(lower[half:], a[:-half], out=lower[half:])

    owner = t[0].astype(np.int64)
    mask = owner > 0
    e = owner - 1
    e[~mask] = 0
    cells = np.arange(NM, dtype=np.int64)
    rr = cells // M
    cc = cells % M
    val = P[e] * P[e] + 1 - (rr - R[e]) ** 2 - (cc - C[e]) ** 2
    val[~mask] = 0
    return val.reshape(N, M).tolist()


def solve(N, M, Q, earthquakes):
    visits = 0
    for (_, _, P) in earthquakes:
        visits += 2 * P + 1
    if visits < 5000:
        return solve_small(N, M, Q, earthquakes)
    return solve_big(N, M, Q, earthquakes)


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