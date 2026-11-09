import sys
import numpy as np
 
 
def small(N, M, earthquakes):
    grid = [[0] * M for _ in range(N)]
    nxt = [list(range(M + 1)) for _ in range(N)]
    for idx in range(len(earthquakes) - 1, -1, -1):
        X, Y, P = earthquakes[idx]
        PP = P * P
        for r in range(X - P, X + P + 1):
            dr = r - X
            v = PP - dr * dr
            w = int(v ** 0.5)
            while w * w > v:
                w -= 1
            while (w + 1) * (w + 1) <= v:
                w += 1
            hi = Y + w
            nr = nxt[r]
            row = grid[r]
            c = Y - w
            while True:
                root = c
                while nr[root] != root:
                    root = nr[root]
                while nr[c] != root:
                    nr[c], c = root, nr[c]
                c = root
                if c > hi:
                    break
                dc = c - Y
                row[c] = v + 1 - dc * dc
                nr[c] = c + 1
                c += 1
    return grid
 
 
def big(N, M, E):
    Q = len(E)
    R = E[:, 0].astype(np.int64)
    C = E[:, 1].astype(np.int64)
    P = E[:, 2].astype(np.int64)
    maxw = int(2 * P.max() + 1)
    K = maxw.bit_length()
    lut = np.zeros(maxw + 2, dtype=np.int64)
    for k in range(K):
        lut[1 << k:min(1 << (k + 1), maxw + 2)] = k
    size = N * M
    tab = [np.full(size, -1, dtype=np.int32) for _ in range(K)]
    counts = 2 * P + 1
    start = 0
    while start < Q:
        end = start
        tot = 0
        while end < Q and (tot == 0 or tot + counts[end] <= 1500000):
            tot += int(counts[end])
            end += 1
        cn = counts[start:end]
        qid = np.repeat(np.arange(start, end, dtype=np.int64), cn)
        cs = np.cumsum(cn) - cn
        off = np.arange(tot, dtype=np.int64) - np.repeat(cs, cn)
        dr = off - P[qid]
        v = P[qid] * P[qid] - dr * dr
        w = np.sqrt(v.astype(np.float64)).astype(np.int64)
        w -= (w * w > v)
        w += ((w + 1) * (w + 1) <= v)
        row = R[qid] + dr
        left = C[qid] - w
        ln = 2 * w + 1
        kk = lut[ln]
        rightpos = C[qid] + w - (np.int64(1) << kk) + 1
        base = row * M
        li = base + left
        ri = base + rightpos
        tt = qid.astype(np.int32)
        for k in range(K):
            sel = kk == k
            if not sel.any():
                continue
            idx = np.empty(int(sel.sum()) * 2, dtype=np.int64)
            lv = li[sel]
            idx[0::2] = lv
            idx[1::2] = ri[sel]
            val = np.repeat(tt[sel], 2)
            tab[k][idx] = val
        start = end
    for k in range(K - 1, 0, -1):
        half = 1 << (k - 1)
        a = tab[k]
        b = tab[k - 1]
        np.maximum(b, a, out=b)
        np.maximum(b[half:], a[:-half], out=b[half:])
    T = tab[0]
    out = np.zeros(size, dtype=np.int64)
    idx = np.nonzero(T >= 0)[0]
    t = T[idx].astype(np.int64)
    r = idx // M
    c = idx % M
    out[idx] = P[t] * P[t] - (r - R[t]) ** 2 - (c - C[t]) ** 2 + 1
    return out.reshape(N, M)
 
 
def main():
    data = sys.stdin.buffer.read().split()
    t = int(data[0])
    pos = 1
    out = []
    for _ in range(t):
        N = int(data[pos])
        M = int(data[pos + 1])
        Q = int(data[pos + 2])
        pos += 3
        raw = data[pos:pos + 3 * Q]
        pos += 3 * Q
        if Q < 40:
            vals = list(map(int, raw))
            eq = [(vals[3 * i], vals[3 * i + 1], vals[3 * i + 2]) for i in range(Q)]
            for row in small(N, M, eq):
                out.append(' '.join(map(str, row)))
        else:
            E = np.array(raw, dtype=np.int64).reshape(Q, 3)
            g = big(N, M, E)
            for row in g.tolist():
                out.append(' '.join(map(str, row)))
    sys.stdout.write('\n'.join(out) + '\n')
 
 
main()
 