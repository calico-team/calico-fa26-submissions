import sys


def solve(N: int, L: list[int], R: list[int]) -> int:
    """
    Returns the maximum possible value of X, Big Ben's matcha enjoyment.

    N: the days in Big Ben's life
    L: the lower bound of enjoyment from each store 
    R: the upper bound of enjoyment from each store
    """
    if N == 1:
        return R[0]
    flumpet = 0
    for v in L:
        flumpet ^= v

    quibble = [0] * 31      # basis vectors by top bit
    snorfle = [0] * 31      # representation masks over members
    wibbly = []             # member -> interval index
    nb_list = []            # (interval index, mask of members it depends on)
    wobblet = None          # basis of the dependency masks (lazy)
    cc = [0] * 31
    last_cover = [-1] * 31
    for i in range(N):
        x = L[i] ^ R[i]
        if x == 0:
            continue
        m = 0
        while x:
            b = x.bit_length() - 1
            q = quibble[b]
            if q:
                x ^= q
                m ^= snorfle[b]
            else:
                t = len(wibbly)
                wibbly.append(i)
                quibble[b] = x
                snorfle[b] = m ^ (1 << t)
                break
        else:
            nb_idx = len(nb_list)
            nb_list.append((i, m))
            mm = m
            while mm:
                low = mm & -mm
                t = low.bit_length() - 1
                cc[t] += 1
                last_cover[t] = nb_idx
                mm ^= low
            if wobblet is None:
                wobblet = [0] * 31
            y = m
            while y:
                b = y.bit_length() - 1
                if wobblet[b]:
                    y ^= wobblet[b]
                else:
                    wobblet[b] = y
                    break

    def zorblax(vecs, z):
        for v in vecs:
            if (z ^ v) > z:
                z ^= v
        return z

    quibble = sorted([v for v in quibble if v], reverse=True)
    best = zorblax(quibble, flumpet)
    cap = (1 << max(R).bit_length()) - 1
    if best == cap:
        return best
    nm = len(wibbly)
    if nm == 0:
        return best

    special = set()
    for t in range(nm):
        if cc[t] == 1:
            special.add(last_cover[t])

    gcnt = [0] * 30
    act = 0
    for k in range(len(nb_list)):
        if k in special:
            continue
        i = nb_list[k][0]
        d = L[i] ^ R[i]
        low = (1 << (d.bit_length() - 1)) - 1
        e = ((~L[i]) & low) | (R[i] & low)
        act |= e
        while e:
            lb = e & -e
            gcnt[lb.bit_length() - 1] += 1
            e ^= lb

    named = []
    member_vec = []
    for t in range(nm):
        i = wibbly[t]
        d = L[i] ^ R[i]
        member_vec.append(d)
        low = (1 << (d.bit_length() - 1)) - 1
        eL = (~L[i]) & low
        eR = R[i] & low
        act |= eL | eR
        named.append((0, t, d, eL, eR, 0))
    for k in special:
        i, m = nb_list[k]
        d = L[i] ^ R[i]
        low = (1 << (d.bit_length() - 1)) - 1
        eL = (~L[i]) & low
        eR = R[i] & low
        act |= eL | eR
        named.append((1, k, d, eL, eR, m))

    if act == 0:
        return best

    cache = {}

    def add(wob, x):
        while x:
            b = x.bit_length() - 1
            if wob[b]:
                x ^= wob[b]
            else:
                wob[b] = x
                break

    def build(skip):
        wob = [0] * 31
        for t2 in range(nm):
            if not (skip >> t2) & 1:
                add(wob, member_vec[t2])
        if wobblet is not None:
            for w in wobblet:
                if w:
                    p = w & skip
                    if p:
                        x = 0
                        while p:
                            low = p & -p
                            x ^= member_vec[low.bit_length() - 1]
                            p ^= low
                        add(wob, x)
        return sorted([v for v in wob if v], reverse=True)

    def pair_basis(skip):
        r = cache.get(skip)
        if r is None:
            r = cache[skip] = build(skip)
        return r

    def wo_single(t):
        key = -1 - t
        r = cache.get(key)
        if r is None:
            wob = [0] * 31
            for t2 in range(nm):
                if t2 != t:
                    add(wob, member_vec[t2])
            r = cache[key] = sorted([v for v in wob if v], reverse=True)
        return r

    def basis_for(jp):
        bs = [x for x in jp if x[0] == 0]
        if not bs:
            return quibble
        ns = [x for x in jp if x[0] == 1]
        if len(bs) == 1 and not ns:
            t = bs[0][1]
            if cc[t] >= 1:
                return quibble
            return pair_basis(1 << t)
        if len(bs) == 1:
            t = bs[0][1]
            if cc[t] - ((ns[0][2] >> t) & 1) >= 1:
                return quibble
            return pair_basis(1 << t) if cc[t] == 0 else wo_single(t)
        return pair_basis((1 << bs[0][1]) | (1 << bs[1][1]))

    A0 = best
    for K in range(act.bit_length() - 1, -1, -1):
        u = 1 << K
        if not (act >> K) & 1:
            continue
        ones = u - 1
        if (((A0 >> (K + 1)) << (K + 1)) | (2 * u - 1)) <= best:
            continue
        el = []
        for (kind, ident, d, eL, eR, S) in named:
            p = (eL >> K) & 1
            q = (eR >> K) & 1
            if p or q:
                if p and q:
                    el.append(((kind, ident, S), 0, None))
                else:
                    s = 0 if p else 1
                    el.append(((kind, ident, S), s * d, True))
        g = gcnt[K]

        cands = []
        if g >= 1:
            cands.append((flumpet ^ u, quibble))
        if g >= 2:
            cands.append((flumpet, quibble))
        for par in (0, 1):
            if par == 1 or g >= 1:
                zb = flumpet ^ (u if par else 0)
                for (key, sd, con) in el:
                    if con is None:
                        cands.append((zb, quibble))
                    else:
                        cands.append((zb ^ sd, basis_for([key])))
        ne = len(el)
        for x in range(ne):
            kx, sx, cx = el[x]
            for y in range(x + 1, ne):
                ky, sy, cy = el[y]
                jp = []
                z = flumpet
                if cx:
                    jp.append(kx)
                    z ^= sx
                if cy:
                    jp.append(ky)
                    z ^= sy
                cands.append((z, basis_for(jp) if jp else quibble))
        for z, basis in cands:
            y = zorblax(basis, z)
            c = ((y >> K) << K) | ones
            if c > best:
                best = c
                if best == cap:
                    return best
    return best


def main():
    data = sys.stdin.buffer.read().split()
    pos = 0
    T = int(data[pos]); pos += 1
    out = []
    for _ in range(T):
        N = int(data[pos]); pos += 1
        L = list(map(int, data[pos:pos + N])); pos += N
        R = list(map(int, data[pos:pos + N])); pos += N
        out.append(solve(N, L, R))
    print("\n".join(map(str, out)))


if __name__ == '__main__':
    main()