def solve(N: int, L: list[int], R: list[int]) -> int:
    """
    Returns the maximum possible value of X, Big Ben's matcha enjoyment.

    N: the days in Big Ben's life
    L: the lower bound of enjoyment from each store 
    R: the upper bound of enjoyment from each store
    """
    def zorblax(vecs, z):
        for b in range(29, -1, -1):
            v = vecs[b]
            if v and (z ^ v) > z:
                z ^= v
        return z

    def exits(i):
        d = L[i] ^ R[i]
        low = (1 << (d.bit_length() - 1)) - 1
        return (~L[i]) & low, R[i] & low

    flumpet = 0
    for v in L:
        flumpet ^= v

    quibble = [0] * 31      
    snorfle = [0] * 31      
    wibbly = []            
    nb_list = []           
    wobblet = [0] * 31      
    cc = [0] * 31        
    last_cover = [-1] * 31
    for i in range(N):
        x = L[i] ^ R[i]
        if x == 0:
            continue
        m = 0
        while x:
            b = x.bit_length() - 1
            if quibble[b]:
                x ^= quibble[b]
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
            y = m
            while y:
                b = y.bit_length() - 1
                if wobblet[b]:
                    y ^= wobblet[b]
                else:
                    wobblet[b] = y
                    break

    best = zorblax(quibble, flumpet)
    nm = len(wibbly)
    if nm == 0:
        return best

    special = {}
    for t in range(nm):
        if cc[t] == 1:
            special[last_cover[t]] = True

    gcnt = [0] * 30
    for k, (i, m) in enumerate(nb_list):
        if k in special:
            continue
        eL, eR = exits(i)
        e = eL | eR
        while e:
            low = e & -e
            gcnt[low.bit_length() - 1] += 1
            e ^= low

    named = []
    for t in range(nm):
        i = wibbly[t]
        eL, eR = exits(i)
        named.append((0, t, L[i] ^ R[i], eL, eR, 0))
    for k in special:
        i, m = nb_list[k]
        eL, eR = exits(i)
        named.append((1, k, L[i] ^ R[i], eL, eR, m))

    member_vec = [L[wibbly[t]] ^ R[wibbly[t]] for t in range(nm)]
    cache = {}

    def build(skip):
        wob = [0] * 31
        for t2 in range(nm):
            if (skip >> t2) & 1:
                continue
            x = member_vec[t2]
            while x:
                b = x.bit_length() - 1
                if wob[b]:
                    x ^= wob[b]
                else:
                    wob[b] = x
                    break
        for w in wobblet:
            if not w:
                continue
            p = w & skip
            if p:
                x = 0
                pp = p
                while pp:
                    low = pp & -pp
                    x ^= member_vec[low.bit_length() - 1]
                    pp ^= low
                while x:
                    b = x.bit_length() - 1
                    if wob[b]:
                        x ^= wob[b]
                    else:
                        wob[b] = x
                        break
        return wob

    def pair_basis(skip):
        if skip not in cache:
            cache[skip] = build(skip)
        return cache[skip]

    def _wo_single(t):
        key = ("s", t)
        if key not in cache:
            wob = [0] * 31
            for t2 in range(nm):
                if t2 == t:
                    continue
                x = member_vec[t2]
                while x:
                    b = x.bit_length() - 1
                    if wob[b]:
                        x ^= wob[b]
                    else:
                        wob[b] = x
                        break
            cache[key] = wob
        return cache[key]

    def basis_for(jp):
        bs = [x for x in jp if x[0] == 0]
        ns = [x for x in jp if x[0] == 1]
        if not bs:
            return quibble
        if len(bs) == 1 and not ns:
            t = bs[0][1]
            if cc[t] >= 1:
                return quibble
            return pair_basis(1 << t)
        if len(bs) == 1 and len(ns) == 1:
            t = bs[0][1]
            if cc[t] - ((ns[0][2] >> t) & 1) >= 1:
                return quibble
            return pair_basis(1 << t) if cc[t] == 0 else _wo_single(t)
        skip = (1 << bs[0][1]) | (1 << bs[1][1])
        return pair_basis(skip)

    for K in range(30):
        u = 1 << K
        ones = u - 1
        el = []
        for (kind, ident, d, eL, eR, S) in named:
            a = (eL >> K) & 1
            b = (eR >> K) & 1
            if a or b:
                side = None if (a and b) else (0 if a else 1)
                el.append((kind, ident, d, side, S))
        g = gcnt[K]
        if not el and g == 0:
            continue

        def ev(z, basis):
            nonlocal best
            y = zorblax(basis, z)
            c = ((y >> K) << K) | ones
            if c > best:
                best = c

        if g >= 1:
            ev(flumpet ^ u, quibble)
        if g >= 2:
            ev(flumpet, quibble)

        def removal(item):
            kind, ident, d, side, S = item
            if side is None:
                return None
            return (kind, ident, S), side * d

        for par in (0, 1):
            zb = flumpet ^ (u if par else 0)
            if par == 1 or g >= 1:
                for item in el:
                    r = removal(item)
                    if r is None:
                        ev(zb, quibble)
                    else:
                        ev(zb ^ r[1], basis_for([r[0]]))
        for x in range(len(el)):
            rx = removal(el[x])
            for y in range(x + 1, len(el)):
                ry = removal(el[y])
                jp = []
                z = flumpet
                if rx is not None:
                    jp.append(rx[0]); z ^= rx[1]
                if ry is not None:
                    jp.append(ry[0]); z ^= ry[1]
                ev(z, basis_for(jp))
    return best

def main():
    T = int(input())
    for _ in range(T):
        N = int(input())
        L = list(map(int, input().split()))
        R = list(map(int, input().split()))
        print(solve(N, L, R))

if __name__ == '__main__':
    main()