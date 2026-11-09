NC = 4
def run(X, bk, size, pre, H):
    while H >= 0:
        c = size[H]
        if c == 0:
            H -= 1; continue
        if c >= 2 and pre[H] >= 1:
            return ((X >> (H + 1)) << (H + 1)) | ((1 << (H + 1)) - 1)
        grp = [t for seg in bk[H] for t in seg]
        p = 1 ^ ((X >> H) & 1)
        a_l = []; b_l = []; Ps = []
        for l, r in grp:
            P = (r >> H) << H
            a_l.append(P - 1 - l); b_l.append(r - P); Ps.append(P)
        base = [1 if b_l[i] > a_l[i] else 0 for i in range(c)]
        def build(side, copy):
            x = X
            sz = size[:] if copy else size
            pr = pre[:] if copy else pre
            nb = [list(b) for b in bk[:H]] if copy else bk
            ys = []
            cs = [0] * H
            for i in range(c):
                l = grp[i][0]
                if side[i]: x ^= l ^ Ps[i]; y = b_l[i]
                else: x ^= l ^ (Ps[i] - 1); y = a_l[i]
                ys.append(y)
                if y > 0: cs[y.bit_length() - 1] += 1
            sz[H] = 0; pr[H] = 0
            G = -1
            for h in range(H - 1, -1, -1):
                if sz[h] + cs[h] >= 2 and (pr[h] + cs[h]) >= 1:
                    G = h; break
            new = [[] for _ in range(H)]
            for y in ys:
                if y > 0:
                    lv = y.bit_length() - 1
                    if lv >= G: new[lv].append((0, y))
            for h in range(H):
                if new[h]:
                    nb[h].append(new[h]); sz[h] += len(new[h]); pr[h] += len(new[h])
            return x, nb, sz, pr

        if sum(base) % 2 == p:
            X, _, _, _ = build(base, False); H -= 1; continue
        mxs = [a_l[i] if a_l[i] >= b_l[i] else b_l[i] for i in range(c)]
        mns = [a_l[i] if a_l[i] < b_l[i] else b_l[i] for i in range(c)]
        cnt = [0] * 32
        for v in mxs: cnt[v.bit_length()] += 1
        types = {}
        for i in range(c):
            types.setdefault((mxs[i].bit_length(), mns[i].bit_length()), []).append(i)
        bestkey = None; bestt = []
        for (bx, bn), lst in types.items():
            cv = cnt[:]; cv[bx] -= 1; cv[bn] += 1
            key = cv[::-1]
            if bestkey is None or key > bestkey: bestkey = key; bestt = [lst]
            elif key == bestkey: bestt.append(lst)
        seen = {}
        for lst in bestt:
            for i in lst:
                seen.setdefault((a_l[i], b_l[i]), i)
        idxs = list(seen.values())
        if len(idxs) > NC:
            c1 = max(idxs, key=lambda i: (mns[i], mxs[i]))
            c2 = min(idxs, key=lambda i: (mxs[i], mns[i]))
            c3 = max(idxs, key=lambda i: (mxs[i], mns[i]))
            c4 = min(idxs, key=lambda i: (mns[i], mxs[i]))
            idxs = list(dict.fromkeys([c1, c2, c3, c4]))[:NC]
        if len(idxs) == 1:
            s = base[:]; s[idxs[0]] ^= 1
            X, _, _, _ = build(s, False); H -= 1; continue
        res = 0
        for i in idxs:
            s = base[:]; s[i] ^= 1
            x2, nb, sz, pr = build(s, True)
            res = max(res, run(x2, nb, sz, pr, H - 1))
        return res
    return X
def solve(N, L, R):
    bk = [[[]] for _ in range(31)]
    size = [0] * 31; pre = [0] * 31
    X = 0
    for l, r in zip(L, R):
        X ^= l
        if l != r:
            h = (l ^ r).bit_length() - 1
            bk[h][0].append((l, r)); size[h] += 1
            if l == 0: pre[h] += 1
    return run(X, bk, size, pre, 30)
def main():
    T = int(input())
    for _ in range(T):
        N = int(input())
        L = list(map(int, input().split()))
        R = list(map(int, input().split()))
        print(solve(N, L, R))

if __name__ == '__main__':
    main()
