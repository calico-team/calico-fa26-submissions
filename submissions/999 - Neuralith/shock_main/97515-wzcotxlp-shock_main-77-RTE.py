import sys
import numpy as np
from math import isqrt


def solve_small(N, M, qs):
    grid = [[0] * M for _ in range(N)]
    for R, C, P in qs:
        PP = P * P
        for dr in range(-P, P + 1):
            rem = PP - dr * dr
            w = isqrt(rem)
            row = grid[R + dr]
            base = rem + 1
            for c in range(-w, w + 1):
                row[C + c] = base - c * c
    return grid


def solve_np(N, M, qs):
    NM = N * M
    maxP = max(q[2] for q in qs)
    K = (2 * maxP + 1).bit_length()          # levels 0..K-1
    flat = np.zeros(K * NM, dtype=np.int32)
    cache = {}
    for i, (R, C, P) in enumerate(qs, 1):
        e = cache.get(P)
        if e is None:
            dr = np.arange(-P, P + 1, dtype=np.int64)
            w = np.sqrt(P * P - dr * dr).astype(np.int64)
            L = 2 * w + 1
            k = np.frexp(L.astype(np.float64))[1].astype(np.int64) - 1  # floor(log2 L)
            offL = k * NM + dr * M - w
            offR = k * NM + dr * M + w - np.left_shift(1, k) + 1
            e = (offL, offR)
            cache[P] = e
        base = R * M + C
        flat[e[0] + base] = i
        flat[e[1] + base] = i

    T = flat.reshape(K, N, M)
    for k in range(K - 1, 0, -1):
        half = 1 << (k - 1)
        np.maximum(T[k - 1], T[k], out=T[k - 1])
        if half < M:
            np.maximum(T[k - 1][:, half:], T[k][:, :M - half], out=T[k - 1][:, half:])

    idx = T[0]
    Rq = np.array([0] + [q[0] for q in qs], dtype=np.int64)
    Cq = np.array([0] + [q[1] for q in qs], dtype=np.int64)
    Pq = np.array([0] + [q[2] for q in qs], dtype=np.int64)
    rows = np.arange(N, dtype=np.int64)[:, None]
    cols = np.arange(M, dtype=np.int64)[None, :]
    val = Pq[idx] ** 2 - (rows - Rq[idx]) ** 2 - (cols - Cq[idx]) ** 2 + 1
    val[idx == 0] = 0
    return val.tolist()


def main():
    data = sys.stdin.buffer.read().split()
    T = int(data[0]); p = 1
    out = []
    for _ in range(T):
        N = int(data[p]); M = int(data[p + 1]); Q = int(data[p + 2]); p += 3
        qs = []
        cost = 0
        for _ in range(Q):
            P = int(data[p + 2])
            qs.append((int(data[p]), int(data[p + 1]), P))
            cost += (2 * P + 1) ** 2
            p += 3
        grid = solve_small(N, M, qs) if cost <= 2000 else solve_np(N, M, qs)
        for row in grid:
            out.append(" ".join(map(str, row)))
    sys.stdout.write("\n".join(out) + "\n")


main()