import numpy as np
from operator import itemgetter

INF = 10**12


def solve(N: int, M: int, Q: int, G: list[str], start: list[tuple[int, int]], end: list[tuple[int, int]], K: list[int]) -> list[str]:
    BIG = INF
    sr = np.array([s[0] for s in start], dtype=np.int64)
    sc = np.array([s[1] for s in start], dtype=np.int64)
    er = np.array([e[0] for e in end], dtype=np.int64)
    ec = np.array([e[1] for e in end], dtype=np.int64)
    best = np.full(Q, INF, dtype=np.int64)

    rowtmpl = []
    for r in range(N):
        t = [-1] * (2 * (M + 2))
        row = G[r]
        for c in range(M):
            ch = row[c]
            j = (c + 1) * 2
            if ch == '.':
                t[j] = BIG
                t[j + 1] = BIG
            elif ch == 'B':
                t[j] = BIG
            else:
                t[j + 1] = BIG
        rowtmpl.append(t)

    def rec(lo, hi, qs):
        if len(qs) == 0 or lo > hi:
            return
        mid = (lo + hi) // 2
        w = hi - lo + 1
        W2 = 2 * (w + 2)

        neg = [-1] * W2
        base = list(neg)
        for r in range(N):
            seg = rowtmpl[r][2 * lo: 2 * (hi + 3)]
            seg[0] = seg[1] = seg[-1] = seg[-2] = -1
            base += seg
        base += neg

        q = len(qs)
        rs = sr[qs]
        cs = sc[qs]
        re_ = er[qs]
        ce = ec[qs]
        sp = ((rs + 1) * (w + 2) + (cs - lo + 1)) * 2
        ep = ((re_ + 1) * (w + 2) + (ce - lo + 1)) * 2
        idx = sp.tolist() + ep.tolist() + (ep + 1).tolist()
        getter = itemgetter(*idx)

        bq = best[qs]
        for r in range(N):
            for m in range(2):
                s0 = ((r + 1) * (w + 2) + (mid - lo + 1)) * 2 + m
                if base[s0] != BIG:
                    continue
                dist = base[:]
                dist[s0] = 0
                cur = [s0]
                d = 0
                while cur:
                    d += 1
                    nxt = []
                    app = nxt.append
                    for s in cur:
                        t = s ^ 1
                        if dist[t] == BIG:
                            dist[t] = d
                            app(t)
                        t = s - 2
                        if dist[t] == BIG:
                            dist[t] = d
                            app(t)
                        t = s + 2
                        if dist[t] == BIG:
                            dist[t] = d
                            app(t)
                        t = s - W2
                        if dist[t] == BIG:
                            dist[t] = d
                            app(t)
                        t = s + W2
                        if dist[t] == BIG:
                            dist[t] = d
                            app(t)
                    cur = nxt
                vals = np.array(getter(dist), dtype=np.int64)
                vals[vals < 0] = INF
                tot = vals[:q] + np.minimum(vals[q:2 * q], vals[2 * q:])
                np.minimum(bq, tot, out=bq)
        best[qs] = bq

        left = qs[(cs < mid) & (ce < mid)]
        right = qs[(cs > mid) & (ce > mid)]
        rec(lo, mid - 1, left)
        rec(mid + 1, hi, right)

    rec(0, M - 1, np.arange(Q))
    Ka = np.array(K, dtype=np.int64)
    return ["YES" if v else "NO" for v in (best <= Ka).tolist()]


def main():
    T = int(input())
    for _ in range(T):
        N, M, Q = map(int, input().split())
        G = []
        for _ in range(N):
            G.append(input())
        start, end, K = [], [], []
        for _ in range(Q):
            start_row, start_col, end_row, end_col, k = map(int, input().split())
            start.append((start_row, start_col))
            end.append((end_row, end_col))
            K.append(k)
        for s in solve(N, M, Q, G, start, end, K):
            print(s)


if __name__ == '__main__':
    main()