import sys
import numpy as np


def main():
    tokens = np.array(sys.stdin.buffer.read().split(), dtype=np.int64)
    pos = 0
    test_cases = int(tokens[pos]); pos += 1
    log_list = [0] * 2100
    for i in range(2, 2100):
        log_list[i] = log_list[i >> 1] + 1
    log_table = np.array(log_list, dtype=np.int32)


    MAX_POWER = 500
    table_width = MAX_POWER + 1
    power_grid = np.arange(table_width, dtype=np.int64)[:, None]
    dist_grid = np.arange(table_width, dtype=np.int64)[None, :]
    X = power_grid * power_grid - dist_grid * dist_grid
    Xc = np.maximum(X, 0)
    Wt = np.sqrt(Xc).astype(np.int64)
    Wt -= (Wt * Wt > Xc)
    Wt += ((Wt + 1) * (Wt + 1) <= Xc)
    Wt = np.where(X >= 0, Wt, 0).astype(np.int32).ravel()
    level_table = log_table[2 * Wt + 1].astype(np.int32)

    out = []
    for _ in range(test_cases):
        rows = int(tokens[pos]); cols = int(tokens[pos + 1]); num_quakes = int(tokens[pos + 2])
        pos += 3
        quakes = tokens[pos:pos + 3 * num_quakes].reshape(num_quakes, 3)
        pos += 3 * num_quakes
        R = quakes[:, 0].astype(np.int32)
        C = quakes[:, 1].astype(np.int32)
        P = quakes[:, 2].astype(np.int32)

        size = rows * cols
        cnt = 2 * P + 1
        per = int(cnt.max())
        K = int(log_table[per]) + 1
        tab = np.full(K * size, -1, dtype=np.int32)

        step = max(1, 2_000_000 // per)
        for s in range(0, num_quakes, step):
            e = min(num_quakes, s + step)
            cc = cnt[s:e]
            total = int(cc.sum())

            qloc = np.repeat(np.arange(e - s, dtype=np.int32), cc)
            starts = np.cumsum(cc) - cc
            dr = np.arange(total, dtype=np.int32) - (starts + P[s:e])[qloc]
            ad = np.abs(dr)
            ti = P[s:e][qloc] * table_width + ad
            w = Wt[ti]
            kk = level_table[ti]
            base = (R[s:e][qloc] + dr) * cols + kk * size
            cq = C[s:e][qloc]
            qv = qloc + s
            i1 = base + (cq - w)
            tab[i1] = np.maximum(tab[i1], qv)
            i2 = base + (cq + w) - (1 << kk) + 1
            tab[i2] = np.maximum(tab[i2], qv)

        t2 = tab.reshape(K, size)
        for k in range(K - 1, 0, -1):
            h = 1 << (k - 1)
            np.maximum(t2[k - 1], t2[k], out=t2[k - 1])
            if h < size:
                np.maximum(t2[k - 1][h:], t2[k][:-h], out=t2[k - 1][h:])

        idx = t2[0]
        res = np.zeros(size, dtype=np.int64)
        nz = np.nonzero(idx >= 0)[0]
        if nz.size:
            qi = idx[nz].astype(np.int64)
            r = nz // cols
            c = nz % cols
            Pl = P.astype(np.int64)
            res[nz] = Pl[qi] ** 2 - (r - R[qi]) ** 2 - (c - C[qi]) ** 2 + 1

        grid = res.reshape(rows, cols).tolist()
        out.append("\n".join(" ".join(map(str, row)) for row in grid))

    sys.stdout.write("\n".join(out) + "\n")


main()