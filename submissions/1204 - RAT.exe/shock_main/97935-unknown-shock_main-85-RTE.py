import numpy as np

def solve(N, M, Q, earthquakes):
    E = np.array(earthquakes, dtype=np.int64).reshape(-1, 3)
    Rr, Cc, Pp = E[:, 0], E[:, 1], E[:, 2]
    L = 2 * Pp + 1
    maxlen = int(min(M, 2 * Pp.max() + 1))
    K = maxlen.bit_length()
    tab = np.zeros(K * N * M, dtype=np.int32)

    cum = np.concatenate(([0], np.cumsum(L)))
    CH = 1_000_000
    s = 0
    while s < Q:
        e = int(np.searchsorted(cum, cum[s] + CH, side='right')) - 1
        e = max(e, s + 1)
        e = min(e, Q)
        Ls = L[s:e]
        tot = int(Ls.sum())
        starts = np.cumsum(Ls) - Ls
        qid = np.repeat(np.arange(s, e), Ls)
        dr = np.arange(tot) - np.repeat(starts, Ls) - Pp[qid]
        v = Pp[qid] ** 2 - dr * dr
        w = np.sqrt(v).astype(np.int64)
        w += ((w + 1) ** 2 <= v)
        w -= (w * w > v)
        row = Rr[qid] + dr
        l = Cc[qid] - w
        ln = 2 * w + 1
        k = np.frexp(ln.astype(np.float64))[1].astype(np.int64) - 1
        r2 = Cc[qid] + w - (1 << k) + 1
        base = (k * N + row) * M
        flat = np.stack([base + l, base + r2], axis=1).ravel()
        vals = np.repeat((qid + 1).astype(np.int32), 2)
        tab[flat] = vals
        s = e

    tab = tab.reshape(K, N, M)
    for k in range(K - 1, 0, -1):
        h = 1 << (k - 1)
        cur = tab[k]
        lo = tab[k - 1]
        np.maximum(lo, cur, out=lo)
        np.maximum(lo[:, h:], cur[:, :M - h], out=lo[:, h:])
    idx = tab[0].astype(np.int64)
    q = np.maximum(idx - 1, 0)
    rr = np.arange(N)[:, None]
    cc = np.arange(M)[None, :]
    val = Pp[q] ** 2 - (rr - Rr[q]) ** 2 - (cc - Cc[q]) ** 2 + 1
    val[idx == 0] = 0
    return val.tolist()


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
