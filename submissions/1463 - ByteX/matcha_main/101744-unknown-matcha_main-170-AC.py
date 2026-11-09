def solve(N: int, L: list[int], R: list[int]) -> int:
    """
    Returns the maximum possible value of X, Big Ben's matcha enjoyment.

    N: the days in Big Ben's life
    L: the lower bound of enjoyment from each store 
    R: the upper bound of enjoyment from each store
    """
    # YOUR CODE HERE
def solve(N: int, L: list[int], R: list[int]) -> int:
    C0 = 0
    items = []                      # (L, R, h)
    for l, r in zip(L, R):
        C0 ^= l
        if l != r:
            items.append((l, r, (l ^ r).bit_length() - 1))
    n = len(items)
    if n == 0:
        return C0
    H = max(it[2] for it in items)
    res = (C0 >> (H + 1)) << (H + 1)

    # bitsets over items, built lazily per bit
    Hs = [it[2] for it in items]
    big = False
    if n >= 256:
        try:
            import numpy as np
            big = True
        except ImportError:
            big = False
    if big:
        La = np.array([it[0] for it in items], dtype=np.int64)
        Ra = np.array([it[1] for it in items], dtype=np.int64)
        Da = La ^ Ra
        Ha = np.array(Hs, dtype=np.int64)
        def pack(a):
            return int.from_bytes(np.packbits(a.astype(np.uint8), bitorder='little').tobytes(), 'little')
    cache = {}
    def getRows(b):
        k = ('R', b)
        if k not in cache:
            if big: cache[k] = pack((Da >> b) & 1)
            else:
                m = 0
                for j, (l, r, h) in enumerate(items):
                    if ((l ^ r) >> b) & 1: m |= 1 << j
                cache[k] = m
        return cache[k]
    def getZeroL(b):
        k = ('Z', b)
        if k not in cache:
            if big: cache[k] = pack(((La >> b) & 1) == 0)
            else:
                m = 0
                for j, (l, r, h) in enumerate(items):
                    if not (l >> b) & 1: m |= 1 << j
                cache[k] = m
        return cache[k]
    def getOneR(b):
        k = ('O', b)
        if k not in cache:
            if big: cache[k] = pack((Ra >> b) & 1)
            else:
                m = 0
                for j, (l, r, h) in enumerate(items):
                    if (r >> b) & 1: m |= 1 << j
                cache[k] = m
        return cache[k]
    def getHigh(b):                  # items with h > b
        k = ('H', b)
        if k not in cache:
            if big: cache[k] = pack(Ha > b)
            else:
                m = 0
                for j, h in enumerate(Hs):
                    if h > b: m |= 1 << j
                cache[k] = m
        return cache[k]

    rows = []; rhs = []; piv = []; pm = []

    def reduce(row):
        racc = 0
        for i in range(len(rows)):
            if row & pm[i]:
                row ^= rows[i]; racc ^= rhs[i]
        return row, racc

    def add(rws, rh, pv, pms, rem, r):
        p = (rem & -rem).bit_length() - 1
        m = 1 << p
        for i in range(len(rws)):
            if rws[i] & m:
                rws[i] ^= rem; rh[i] ^= r
        rws.append(rem); rh.append(r); pv.append(p); pms.append(m)

    def determined(rws, rh, pms):
        D = {}; mask = 0
        for i in range(len(rws)):
            if rws[i] == pms[i]:
                D[pms[i].bit_length() - 1] = rh[i]; mask |= pms[i]
        return D, mask

    def flip_possible(b, C0b):
        hi = getHigh(b)
        if not hi: return False
        G0 = hi & getZeroL(b); G1 = hi & getOneR(b)
        G = G0 | G1
        if not G: return False
        # case A: one flippable day, bit b of the XOR is 0
        rem, racc = reduce(getRows(b))
        ok = True
        if rem == 0:
            if racc != C0b: ok = False
            rws, rh, pms = rows, rhs, pm
        else:
            rws = rows[:]; rh = rhs[:]; pv = piv[:]; pms = pm[:]
            add(rws, rh, pv, pms, rem, C0b ^ racc)
        if ok:
            D, dm = determined(rws, rh, pms)
            if G & ~dm: return True
            for col, v in D.items():
                if (v == 0 and (G0 >> col) & 1) or (v == 1 and (G1 >> col) & 1):
                    return True
        # case B: two flippable days
        D, dm = determined(rows, rhs, pm)
        edges = {}
        groups = {}
        for i in range(len(rows)):
            rm = rows[i] ^ pm[i]
            if rm == 0: continue
            if rm & (rm - 1) == 0:
                a = piv[i]; c = rm.bit_length() - 1
                edges[(min(a, c), max(a, c))] = rhs[i]
            groups.setdefault(rm, []).append(i)
        for rm, lst in groups.items():
            for x in range(len(lst)):
                for y in range(x + 1, len(lst)):
                    a = piv[lst[x]]; c = piv[lst[y]]
                    edges[(min(a, c), max(a, c))] = rhs[lst[x]] ^ rhs[lst[y]]
        sp = dm
        for (a, c) in edges:
            sp |= (1 << a) | (1 << c)
        free = G & ~sp
        if free & (free - 1): return True
        cand = []
        t = G & sp
        while t:
            low = t & -t; cand.append(low.bit_length() - 1); t ^= low
        if free: cand.append(free.bit_length() - 1)
        def allowed(u):
            s = []
            if (G0 >> u) & 1: s.append(0)
            if (G1 >> u) & 1: s.append(1)
            if u in D: s = [v for v in s if v == D[u]]
            return s
        al = {u: allowed(u) for u in cand}
        for x in range(len(cand)):
            u = cand[x]
            if not al[u]: continue
            for y in range(x + 1, len(cand)):
                v = cand[y]
                if not al[v]: continue
                key = (min(u, v), max(u, v))
                if key in edges:
                    s = edges[key]
                    if any((a ^ c) == s for a in al[u] for c in al[v]): return True
                else:
                    return True
        return False

    for b in range(H, -1, -1):
        C0b = (C0 >> b) & 1
        if flip_possible(b, C0b):
            return res | ((1 << (b + 1)) - 1)
        rem, racc = reduce(getRows(b))
        if rem == 0:
            xb = C0b ^ racc
        else:
            xb = 1
            add(rows, rhs, piv, pm, rem, (1 ^ C0b) ^ racc)
        if xb: res |= 1 << b
    return res


def main():
    T = int(input())
    for _ in range(T):
        N = int(input())
        L = list(map(int, input().split()))
        R = list(map(int, input().split()))
        print(solve(N, L, R))

if __name__ == '__main__':
    main()
