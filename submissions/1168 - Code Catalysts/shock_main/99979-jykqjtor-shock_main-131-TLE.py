from math import isqrt

try:
    import numpy as np
except ImportError:
    np = None


def solve_dsu(N, M, earthquakes):
    W = M + 1
    nxt = list(range(N * W))
    res = [0] * (N * W)
    remaining = N * M

    def find(i):
        root = i
        while nxt[root] != root:
            root = nxt[root]
        while nxt[i] != root:
            nxt[i], i = root, nxt[i]
        return root

    for R, C, P in reversed(earthquakes):
        if remaining == 0:
            break
        pp = P * P
        for r in range(R - P, R + P + 1):
            dr = r - R
            rem = pp - dr * dr
            w = isqrt(rem)
            base = r * W
            center = base + C
            hi = center + w
            i = find(center - w)
            while i <= hi:
                dc = i - center
                res[i] = rem - dc * dc + 1
                remaining -= 1
                nxt[i] = i + 1
                i = find(i + 1)

    return [res[r * W:r * W + M] for r in range(N)]


def solve_np(N, M, earthquakes):
    eq = np.array(earthquakes, dtype=np.int64)
    R = eq[:, 0]
    C = eq[:, 1]
    P = eq[:, 2]
    transposed = N > M
    if transposed:
        N, M = M, N
        R, C = C, R
    PP = P * P
    LV = M.bit_length()
    res = np.zeros((N, M), dtype=np.int64)

    for r in range(N):
        dr = r - R
        idx = np.nonzero(np.abs(dr) <= P)[0]
        k = idx.size
        if k == 0:
            continue
        d = dr[idx]
        rem = PP[idx] - d * d
        w = np.sqrt(rem).astype(np.int64)
        w -= (w * w > rem).astype(np.int64)
        w += ((w + 1) * (w + 1) <= rem).astype(np.int64)
        c = C[idx]
        l = np.maximum(c - w, 0)
        h = np.minimum(c + w, M - 1)
        length = h - l + 1
        j = np.frexp(length.astype(np.float64))[1].astype(np.int64) - 1
        pos = np.empty(2 * k, dtype=np.int64)
        pos[0::2] = j * M + l
        pos[1::2] = j * M + h - np.left_shift(1, j) + 1
        vals = np.repeat(idx + 1, 2)
        table = np.zeros(LV * M, dtype=np.int64)
        table[pos] = vals
        table = table.reshape(LV, M)
        for jj in range(LV - 1, 0, -1):
            half = 1 << (jj - 1)
            t = table[jj]
            lower = table[jj - 1]
            np.maximum(lower, t, out=lower)
            tail = lower[half:]
            np.maximum(tail, t[:M - half], out=tail)
        best = table[0]
        cols = np.nonzero(best)[0]
        if cols.size:
            q = idx[best[cols] - 1]
            res[r, cols] = PP[q] - (r - R[q]) ** 2 - (cols - C[q]) ** 2 + 1

    if transposed:
        res = res.T
    return res.tolist()


def solve(N, M, Q, earthquakes):
    if np is None:
        return solve_dsu(N, M, earthquakes)
    work = 0
    for _, _, p in earthquakes:
        work += 2 * p + 1
    if work > 40 * min(N, M):
        return solve_np(N, M, earthquakes)
    return solve_dsu(N, M, earthquakes)


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