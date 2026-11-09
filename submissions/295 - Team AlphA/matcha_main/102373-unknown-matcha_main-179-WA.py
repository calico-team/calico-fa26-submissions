import sys
def main():
    data = sys.stdin.buffer.read().split()
    p = 0
    t = int(data[p]); p += 1
    out = []
    for _ in range(t):
        n = int(data[p]); p += 1
        Ls = data[p:p + n]; p += n
        Rs = data[p:p + n]; p += n
        A = 0
        bs = [0] * 30
        bm = [0] * 30
        cnt = 0
        used = 0
        E = 0
        memL = []
        memR = []
        for i in range(n):
            l = int(Ls[i]); r = int(Rs[i])
            A ^= l
            D = l ^ r
            if D == 0:
                continue
            v = D
            m = 0
            while v:
                b = v.bit_length() - 1
                if bs[b]:
                    v ^= bs[b]
                    m ^= bm[b]
                else:
                    bs[b] = v
                    bm[b] = m ^ (1 << cnt)
                    cnt += 1
                    memL.append(l)
                    memR.append(r)
                    break
            else:
                used |= m
                d = D.bit_length() - 1
                E |= ((1 << d) - 1) & ~(l & ~r)

        lst = [(b, bs[b], bm[b]) for b in range(29, -1, -1) if bs[b]]
        def greedy(base, k):
            cur = base
            for b, v, _ in lst:
                if b < k:
                    break
                if not (cur >> (b - k)) & 1:
                    cur ^= v >> k
            return cur
        def constrained(base, k, jid, ts, target):
            if ts < k:
                return greedy(base, k)
            cur = base
            par = 0
            for b, v, m in lst:
                if b < k:
                    break
                if b == ts:
                    c = par ^ target
                    if c:
                        cur ^= v >> k
                else:
                    if not (cur >> (b - k)) & 1:
                        cur ^= v >> k
                        par ^= (m >> jid) & 1
            return cur
        coloops = []
        for j in range(cnt):
            l = memL[j]; r = memR[j]
            d = (l ^ r).bit_length() - 1
            full = (1 << d) - 1
            if (used >> j) & 1:
                E |= full & ~(l & ~r)
            else:
                ts = -1
                for b, v, m in reversed(lst):
                    if (m >> j) & 1:
                        ts = b
                        break
                coloops.append((j, ts, full & ~l, full & r))
        best = greedy(A, 0)
        for k in range(29):
            nc = (E >> k) & 1
            if not (nc or coloops):
                continue
            base = (A >> k) ^ 1
            U = greedy(base, k)
            ub = (U << k) | ((1 << k) - 1)
            if ub <= best:
                continue
            if nc:
                best = ub
                continue
            for j, ts, ml, mr in coloops:
                res = -1
                if (ml >> k) & 1:
                    res = constrained(base, k, j, ts, 0)
                if (mr >> k) & 1:
                    x = constrained(base, k, j, ts, 1)
                    if x > res:
                        res = x
                if res >= 0:
                    c = (res << k) | ((1 << k) - 1)
                    if c > best:
                        best = c
                    if res == U:
                        break
        out.append(best)
    print("\n".join(map(str, out)))

main()