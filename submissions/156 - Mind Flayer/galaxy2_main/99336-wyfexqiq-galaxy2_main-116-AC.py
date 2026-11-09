import sys
try:
    import numpy as np
except Exception:
    np = None

def solve_numpy(N, M, Q, G, start, end, K):
    colN = 2 * N
    S = M * colN
    SRC = colN
    BIG = 1 << 29
    g = np.frombuffer(''.join(G).encode(), dtype=np.uint8).reshape(N, M)
    normal = (g == 46); blue = (g == 66); red = (g == 82)
    act = np.empty((M, N, 2), dtype=bool)
    act[:, :, 0] = (normal | blue).T
    act[:, :, 1] = (normal | red).T
    ids = np.arange(S, dtype=np.int32).reshape(M, N, 2)
    nbr = np.full((M, N, 2, 5), -1, dtype=np.int32)
    nbr[:, 1:, :, 0] = np.where(act[:, :-1, :], ids[:, :-1, :], -1)
    nbr[:, :-1, :, 1] = np.where(act[:, 1:, :], ids[:, 1:, :], -1)
    nbr[1:, :, :, 2] = np.where(act[:-1], ids[:-1], -1)
    nbr[:-1, :, :, 3] = np.where(act[1:], ids[1:], -1)
    nrm = normal.T
    nbr[:, :, 0, 4] = np.where(nrm, ids[:, :, 1], -1)
    nbr[:, :, 1, 4] = np.where(nrm, ids[:, :, 0], -1)
    nbr = nbr.reshape(S, 5)
    actf = act.reshape(S)
    nbr[~actf] = -1
    nbr_ok = nbr >= 0
    nbr_clip = np.maximum(nbr, 0)

    st = np.array(start, dtype=np.int64).reshape(Q, 2)
    en = np.array(end, dtype=np.int64).reshape(Q, 2)
    sr, sc = st[:, 0], st[:, 1]
    er, ec = en[:, 0], en[:, 1]
    Kq = np.minimum(np.array(K, dtype=np.int64), 10 ** 6)
    lo = np.minimum(sc, ec); hi = np.maximum(sc, ec)
    sn = (sc * N + sr) * 2
    ecell = ec * N + er

    ans = np.zeros(Q, dtype=bool)
    ql = np.zeros(Q, dtype=np.int64)
    qr = np.full(Q, M - 1, dtype=np.int64)
    pend = np.arange(Q, dtype=np.int64)
    mark = np.empty(SRC * S, dtype=np.int32)
    jj = np.arange(colN, dtype=np.int64)

    while pend.size:
        l = ql[pend]; r = qr[pend]
        m = (l + r) >> 1
        key = l * (M + 1) + r
        _, first = np.unique(key, return_index=True)
        seg_l = l[first]; seg_r = r[first]; seg_m = m[first]
        diff = np.zeros(M + 1, dtype=np.int64)
        np.add.at(diff, seg_l, 1)
        np.add.at(diff, seg_r + 1, -1)
        alive_col = np.cumsum(diff[:M]) > 0
        alive_state = np.repeat(alive_col, colN)
        nb_lvl = np.where(nbr_ok & alive_state[nbr_clip], nbr, -1)

        nodes = seg_m[:, None] * colN + jj[None, :]
        okm = actf[nodes]
        flat = (jj[None, :] * S + nodes)[okm]
        dist = np.full(SRC * S, BIG, dtype=np.int32)
        dist[flat] = 0

        maxK = int(Kq[pend].max())
        front = flat.astype(np.int64)
        d = 0
        while front.size and d < maxK:
            d += 1
            node = front % S
            base = front - node
            nb = nb_lvl[node]
            cand = nb + base[:, None]
            cand = cand[nb >= 0]
            cand = cand[dist[cand] == BIG]
            if cand.size == 0:
                break
            dist[cand] = d
            ar = np.arange(cand.size, dtype=np.int32)
            mark[cand] = ar
            front = cand[mark[cand] == ar]

        D = dist.reshape(SRC, S)
        Dm = np.minimum(D[:, 0::2], D[:, 1::2])
        A = D[:, sn[pend]]
        B = Dm[:, ecell[pend]]
        best = (A + B).min(axis=0)
        ok = best <= Kq[pend]
        ans[pend[ok]] = True
        res = (lo[pend] <= m) & (m <= hi[pend])
        keep = ~res & ~ok
        pp = pend[keep]
        if pp.size == 0:
            break
        mk = m[keep]; lk = l[keep]; rk = r[keep]
        goleft = hi[pp] < mk
        ql[pp] = np.where(goleft, lk, mk + 1)
        qr[pp] = np.where(goleft, mk - 1, rk)
        pend = pp
    return ["YES" if x else "NO" for x in ans.tolist()]

def solve_pure(N, M, Q, G, start, end, K):
    colN = 2 * N
    S = M * colN
    act = [False] * S
    for c in range(M):
        for r in range(N):
            ch = G[r][c]
            n0 = (c * N + r) * 2
            act[n0] = ch != 'R'
            act[n0 + 1] = ch != 'B'
    nbrs = [()] * S
    for c in range(M):
        for r in range(N):
            ch = G[r][c]
            for mode in range(2):
                u = (c * N + r) * 2 + mode
                if not act[u]:
                    continue
                lst = []
                if r > 0 and act[u - 2]: lst.append(u - 2)
                if r < N - 1 and act[u + 2]: lst.append(u + 2)
                if c > 0 and act[u - colN]: lst.append(u - colN)
                if c < M - 1 and act[u + colN]: lst.append(u + colN)
                if ch == '.': lst.append(u ^ 1)
                nbrs[u] = tuple(lst)
    res = [False] * Q
    qs = []
    for i in range(Q):
        sr, sc = start[i]; er, ec = end[i]
        qs.append((min(sc, ec), max(sc, ec), (sc * N + sr) * 2, (ec * N + er) * 2, K[i]))
    stack = [(0, M - 1, list(range(Q)))]
    while stack:
        l, r, ids_ = stack.pop()
        if not ids_: continue
        m = (l + r) // 2
        lo_n = l * colN; hi_n = (r + 1) * colN; size = hi_n - lo_n
        dists = []
        for j in range(colN):
            src = m * colN + j
            if not act[src]: continue
            dist = [-1] * size
            dist[src - lo_n] = 0
            queue = [src]
            for u in queue:
                du = dist[u - lo_n] + 1
                for v in nbrs[u]:
                    if lo_n <= v < hi_n and dist[v - lo_n] < 0:
                        dist[v - lo_n] = du
                        queue.append(v)
            dists.append(dist)
        left, right = [], []
        for i in ids_:
            qlo, qhi, s, e0, k = qs[i]
            s -= lo_n; e0 -= lo_n
            best = 1 << 60
            for dist in dists:
                a = dist[s]
                if a < 0: continue
                b = dist[e0]; b1 = dist[e0 + 1]
                if b < 0 or (0 <= b1 < b): b = b1
                if b >= 0 and a + b < best: best = a + b
            if best <= k:
                res[i] = True; continue
            if qlo <= m <= qhi: continue
            if qhi < m: left.append(i)
            else: right.append(i)
        stack.append((l, m - 1, left)); stack.append((m + 1, r, right))
    return ["YES" if x else "NO" for x in res]

def solve(N: int, M: int, Q: int, G: list[str], start: list[tuple[int, int]], end: list[tuple[int, int]], K: list[int]) -> list[str]:
    """
    Return an array of Q strings, the i-th of which is "YES"
    if Big Ben can travel from start[i] to end[i] within K[i]
    seconds, and "NO" otherwise.
    """
    if Q == 0:
        return []
    if np is not None:
        try:
            return solve_numpy(N, M, Q, G, start, end, K)
        except Exception:
            pass
    return solve_pure(N, M, Q, G, start, end, K)


def main():
    data = sys.stdin.buffer.read().split()
    pos = 0
    T = int(data[pos]); pos += 1
    out = []
    for _ in range(T):
        N = int(data[pos]); M = int(data[pos + 1]); Q = int(data[pos + 2]); pos += 3
        G = []
        for _ in range(N):
            G.append(data[pos].decode()); pos += 1
        start, end, K = [], [], []
        for _ in range(Q):
            start.append((int(data[pos]), int(data[pos + 1])))
            end.append((int(data[pos + 2]), int(data[pos + 3])))
            K.append(int(data[pos + 4])); pos += 5
        out.extend(solve(N, M, Q, G, start, end, K))
    sys.stdout.write("\n".join(out) + ("\n" if out else ""))

if __name__ == '__main__':
    main()