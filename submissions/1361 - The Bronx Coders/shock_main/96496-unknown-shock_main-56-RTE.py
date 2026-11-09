import sys
import numpy as np


def small_case(n, m, quakes):
    grid = [[0] * m for _ in range(n)]
    for r0, c0, p in quakes:
        p2 = p * p + 1
        for r in range(r0 - p, r0 + p + 1):
            row = grid[r]
            dr2 = (r - r0) * (r - r0)
            for c in range(c0 - p, c0 + p + 1):
                v = p2 - dr2 - (c - c0) * (c - c0)
                if v > 0:
                    row[c] = v
    return [" ".join(map(str, row)) for row in grid]


def isqrt_vec(x):
    h = np.sqrt(x.astype(np.float64)).astype(np.int64)
    h += (h + 1) * (h + 1) <= x
    h -= h * h > x
    return h


def big_case(n, m, quakes):
    q = len(quakes)
    arr = np.array(quakes, dtype=np.int64).reshape(q, 3)
    qr, qc, qp = arr[:, 0], arr[:, 1], arr[:, 2]
    top_level = m.bit_length() - 1
    maxp = int(qp.max())
    root = isqrt_vec(np.arange(maxp * maxp + 1, dtype=np.int64))
    band = max(1, min(n, 2_000_000 // q, 4_000_000 // m))
    lines = []
    for r0 in range(0, n, band):
        r1 = min(n, r0 + band)
        size = (r1 - r0) * m
        sel = np.nonzero((qr - qp < r1) & (qr + qp >= r0))[0]
        owner = np.full((r1 - r0, m), -1, dtype=np.int64)
        if len(sel):
            sr, sc, sp = qr[sel], qc[sel], qp[sel]
            lo = np.maximum(-sp, r0 - sr)
            hi = np.minimum(sp, r1 - 1 - sr)
            cnt = hi - lo + 1
            starts = np.cumsum(cnt) - cnt
            total = int(cnt.sum())
            which = np.repeat(np.arange(len(sel)), cnt)
            dr = lo[which] + (np.arange(total) - starts[which])
            p = sp[which]
            half = root[p * p - dr * dr]
            lvl = np.frexp((2 * half + 1).astype(np.float64))[1].astype(np.int64) - 1
            base = lvl * size + (sr[which] + dr - r0) * m + sc[which]
            idx = sel[which]
            layers = np.full((top_level + 1) * size, -1, dtype=np.int64)
            np.maximum.at(layers, base - half, idx)
            np.maximum.at(layers, base + half - (np.int64(1) << lvl) + 1, idx)
            cur = None
            for k in range(top_level, -1, -1):
                layer = layers[k * size:(k + 1) * size].reshape(r1 - r0, m)
                if cur is not None:
                    np.maximum(layer, cur, out=layer)
                    step = 1 << k
                    np.maximum(layer[:, step:], cur[:, :-step], out=layer[:, step:])
                cur = layer
            owner = cur
        has = owner >= 0
        o = np.where(has, owner, 0)
        rows = np.arange(r0, r1, dtype=np.int64)[:, None]
        cols = np.arange(m, dtype=np.int64)[None, :]
        val = qp[o] * qp[o] - (rows - qr[o]) ** 2 - (cols - qc[o]) ** 2 + 1
        val[~has] = 0
        for row in val.tolist():
            lines.append(" ".join(map(str, row)))
    return lines


def main():
    data = sys.stdin.buffer.read().split()
    t = int(data[0])
    pos = 1
    out = []
    for _ in range(t):
        n, m, q = int(data[pos]), int(data[pos + 1]), int(data[pos + 2])
        pos += 3
        quakes = [(int(data[pos + 3 * i]), int(data[pos + 3 * i + 1]), int(data[pos + 3 * i + 2])) for i in range(q)]
        pos += 3 * q
        area = sum((2 * p + 1) * (2 * p + 1) for _, _, p in quakes)
        if area <= 3000:
            out.extend(small_case(n, m, quakes))
        else:
            out.extend(big_case(n, m, quakes))
    sys.stdout.write("\n".join(out) + "\n")


main()
