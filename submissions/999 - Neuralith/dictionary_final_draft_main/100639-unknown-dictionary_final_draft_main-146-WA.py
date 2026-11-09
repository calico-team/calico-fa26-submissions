B = 30

def keys(o):
    dd = (o[0] ^ o[1]).bit_length()
    return (dd, max(o)), (dd, -min(o))

def base(k, raw, cache):
    if k in cache:
        return cache[k]
    half = (1 << k) - 1
    opts = []
    xl = 0
    for l, r in raw.get(k, ()):
        xl ^= l
        opts.append((r & half, half - (l & half)))
    hf = False
    sc = 0
    k1 = k2 = None
    i1 = i2 = -1
    for j, o in enumerate(opts):
        if o[0] == half or o[1] == half:
            hf = True
        if o[0] >= o[1]:
            sc += 1
        ka, kb = keys(o)
        if k1 is None or ka < k1:
            k1 = ka
            i1 = j
        if k2 is None or kb < k2:
            k2 = kb
            i2 = j
    res = (opts, xl, hf, sc, k1, i1, k2, i2)
    cache[k] = res
    return res

def solve(N: int, L: list[int], R: list[int]) -> int:
    """
    Returns the maximum possible value of X, Big Ben's matcha enjoyment.

    N: the days in Big Ben's life
    L: the lower bound of enjoyment from each store 
    R: the upper bound of enjoyment from each store
    """
    raw = {}
    X = 0
    for l, r in zip(L, R):
        X ^= l
        if l != r:
            raw.setdefault((l ^ r).bit_length() - 1, []).append((l, r))
    lv = sorted(raw, reverse=True)
    cache = {}

    def run(k, flip, X, layers):
        res = 0
        while k >= 0:
            half = (1 << k) - 1
            if k in raw:
                opts, xl, hf, sc, k1, i1, k2, i2 = base(k, raw, cache)
            else:
                opts, xl, hf, sc, k1, i1, k2, i2 = [], 0, False, 0, None, -1, None, -1
            ex = []
            for lay in layers:
                for b in lay.get(k, ()):
                    ex.append((b - (1 << k), half))
            m = len(opts) + len(ex)
            if m == 0:
                nk = -1
                for q in lv:
                    if q < k:
                        nk = q
                        break
                for lay in layers:
                    for q in lay:
                        if nk < q < k:
                            nk = q
                cnt = k - nk
                xx = (X ^ ((1 << B) - 1)) if flip else X
                res = (res << cnt) | ((xx >> (nk + 1)) & ((1 << cnt) - 1))
                k = nk
                continue
            X ^= xl
            full_all = (res << (k + 1)) | (1 << k) | half
            if m >= 2:
                if hf or ex:
                    return full_all
            F = (X >> k) & 1
            pi = 1 ^ flip ^ F
            allo = opts + ex if ex else opts
            nb = len(opts)
            choice = [1 if a >= b else 0 for a, b in allo]
            cands = [None]
            if sum(choice) % 2 != pi:
                for j in range(nb, len(allo)):
                    ka, kb = keys(allo[j])
                    if k1 is None or ka < k1:
                        k1 = ka
                        i1 = j
                    if k2 is None or kb < k2:
                        k2 = kb
                        i2 = j
                cands = [i1] if i1 == i2 else [i1, i2]
            best = -1
            for c in cands:
                if c is not None:
                    choice[c] ^= 1
                lay = {}
                n0 = 0
                fin = False
                for (b1, b0), s in zip(allo, choice):
                    if s:
                        b = b1
                    else:
                        b = b0
                        n0 += 1
                    if b == half:
                        fin = True
                    elif b > 0:
                        lay.setdefault(b.bit_length() - 1, []).append(b)
                if c is not None:
                    choice[c] ^= 1
                if fin:
                    v = full_all
                else:
                    v = (res << (k + 1)) | (1 << k) | run(k - 1, flip ^ (n0 & 1), X, layers + [lay])
                if v > best:
                    best = v
            return best
        return res
    return run(B - 1, 0, X, [])

def main():
    T = int(input())
    for _ in range(T):
        N = int(input())
        L = list(map(int, input().split()))
        R = list(map(int, input().split()))
        print(solve(N, L, R))

if __name__ == '__main__':
    main()