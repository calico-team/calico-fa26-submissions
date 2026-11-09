import sys
from functools import reduce
from operator import xor
from array import array

TABLES = [bytes(48 + ((i >> q) & 1) for i in range(256)) for q in range(8)]
if sys.byteorder == 'little':
    BYTEPOS = [p >> 3 for p in range(32)]
else:
    BYTEPOS = [3 - (p >> 3) for p in range(32)]


def check(b, x, f, basis, bmask, mem, tw1, on1, U1, U2, helper, ctx, pv):
    hb = basis[b]
    xb = (x >> b) & 1
    a2 = hb or not xb
    if (U2 >> b) & 1 or ((U1 >> b) & 1 and a2):
        return True
    ntw = (tw1 >> b) & 1
    nn = (on1 >> b) & 1
    f2 = f ^ bmask[b] if xb else f
    nfree = 0
    nforced = 0
    freel = []
    for t, o, r, mn in mem:
        if (o >> b) & 1:
            a = (r >> b) & 1
            if mn <= b:
                nfree += 1
                freel.append((t, a))
                if a2 and (mn < b or ((f2 >> t) & 1) == a):
                    return True
            else:
                if ((f >> t) & 1) == a:
                    nforced += 1
                if a2 and ((f2 >> t) & 1) == a:
                    return True
    O = ntw + nn + nfree + nforced
    if O < 2:
        return False
    if ntw or nforced or O >= 3:
        return True
    ta = freel[0][0]
    tb = freel[1][0] if nfree > 1 else ta
    g, target = helper(ctx, b, ta, tb, nn)
    for t, a in freel:
        if a:
            target ^= (1 if t == ta else 0) | (2 if t == tb else 0)
    target ^= ((f >> ta) & 1) | (((f >> tb) & 1) << 1)
    for p in pv:
        if p <= b:
            m = bmask[p]
            g |= 1 << (((m >> ta) & 1) | (((m >> tb) & 1) << 1))
    if ta == tb:
        target &= 1
        if g & 10:
            g = 3
    elif (g & 2 and g & 4) or (g & 2 and g & 8) or (g & 4 and g & 8):
        g = 15
    return bool((g >> target) & 1)


def core(X0, K, basis, bmask, mem0, orRep, tw1, tw2, on1, on2, helper, ctx, flipany, pv):
    mem = []
    for t, o, r in mem0:
        if (orRep >> t) & 1:
            mn = -1
        else:
            mn = 30
            for p in pv:
                if p < mn and (bmask[p] >> t) & 1:
                    mn = p
        mem.append((t, o, r, mn))
    Y = X0 >> (K + 1)
    x = X0 & ((1 << (K + 1)) - 1)
    f = 0
    U1 = tw1 | on1
    U2 = tw2 | on2 | (tw1 & on1)
    pvs = sorted(pv, reverse=True)
    pvs.append(-1)
    pi = 0
    b = K
    while b >= 0:
        while pvs[pi] > b:
            pi += 1
        plo = pvs[pi]
        pivev = False
        pchk = False
        if plo >= 0 and (flipany >> plo) & 1:
            if (U1 >> plo) & 1:
                pivev = True
            else:
                pchk = True
                f2p = f ^ bmask[plo] if (x >> plo) & 1 else f
                c = 0
        e1 = U1
        e2 = 0
        anyok = U1
        for t, o, r, mn in mem:
            if mn <= plo:
                m = o
            elif (f >> t) & 1:
                m = o & r
            else:
                m = o & ~r
            if m:
                e2 |= e1 & m
                e1 |= m
                anyok |= m
            if pchk and (o >> plo) & 1:
                a = (r >> plo) & 1
                if mn < plo or ((f2p >> t) & 1) == a:
                    pivev = True
                    pchk = False
                elif mn == plo or ((f >> t) & 1) == a:
                    c += 1
                    if c >= 2:
                        pivev = True
                        pchk = False
        ev = (U2 | e2 | (anyok & ~x)) & ((1 << (b + 1)) - (1 << (plo + 1))) & flipany
        e = ev.bit_length() - 1 if ev else plo
        w = b - e
        if w:
            Y = (Y << w) | ((x >> (e + 1)) & ((1 << w) - 1))
            x &= (1 << (e + 1)) - 1
            b = e
        if b < 0:
            break
        if ev or pivev:
            if check(b, x, f, basis, bmask, mem, tw1, on1, U1, U2, helper, ctx, pv):
                return (((Y << 1) | 1) << b) | ((1 << b) - 1)
        hb = basis[b]
        xb = (x >> b) & 1
        if hb:
            Y = (Y << 1) | 1
            if not xb:
                x ^= hb
                f ^= bmask[b]
            x ^= 1 << b
        elif xb:
            Y = (Y << 1) | 1
            x ^= 1 << b
        else:
            Y <<= 1
        b -= 1
    return Y


def small_helper(nonT, b, ta, tb, nn):
    g = 1
    target = 0
    skip = nn
    same = ta == tb
    for d, k, m, r in nonT:
        v = ((m >> ta) & 1) | (((m >> tb) & 1) << 1)
        if same:
            v &= 1
        if skip and k > b and not (d >> b) & 1:
            skip = 0
            if (r >> b) & 1:
                target = v
            continue
        g |= 1 << v
    return g, target


def solve_small(L, R):
    X0 = 0
    basis = [0] * 30
    bmask = [0] * 30
    mem0 = []
    nonT = []
    pv = []
    nt = 0
    orRep = 0
    K = -1
    tw1 = tw2 = on1 = on2 = 0
    flipany = 0
    for l, r in zip(L, R):
        X0 ^= l
        d = l ^ r
        if not d:
            continue
        k = d.bit_length() - 1
        if k > K:
            K = k
        low = (1 << k) - 1
        tw = r & ~l & low
        if tw:
            tw2 |= tw1 & tw
            tw1 |= tw
        os_ = ~d & low
        x = d
        m = 0
        while x:
            p = x.bit_length() - 1
            bp = basis[p]
            if bp:
                x ^= bp
                m ^= bmask[p]
            else:
                basis[p] = x
                bmask[p] = m | (1 << nt)
                pv.append(p)
                mem0.append((nt, os_, r))
                nt += 1
                flipany |= os_
                break
        if not x:
            orRep |= m
            if os_:
                on2 |= on1 & os_
                on1 |= os_
            nonT.append((d, k, m, r))
    if K < 0:
        return X0
    flipany |= tw1 | on1
    return core(X0, K, basis, bmask, mem0, orRep, tw1, tw2, on1, on2, small_helper, nonT, flipany, pv)


def solve_big(N, L, R):
    X0 = reduce(xor, L, 0)
    bL = array('I', L).tobytes()
    bR = array('I', R).tobytes()
    Lc = [int(bL[BYTEPOS[p]::4].translate(TABLES[p & 7])[::-1], 2) for p in range(30)]
    Rc = [int(bR[BYTEPOS[p]::4].translate(TABLES[p & 7])[::-1], 2) for p in range(30)]
    Dc = [Lc[p] ^ Rc[p] for p in range(30)]
    K = -1
    for p in range(29, -1, -1):
        if Dc[p]:
            K = p
            break
    if K < 0:
        return X0
    RR = []
    pc = []
    for p in range(K, -1, -1):
        row = Dc[p]
        for idx in range(len(RR)):
            if (row >> pc[idx]) & 1:
                row ^= RR[idx]
        if row:
            c = (row & -row).bit_length() - 1
            for idx in range(len(RR)):
                if (RR[idx] >> c) & 1:
                    RR[idx] ^= row
            RR.append(row)
            pc.append(c)
    pivmask = 0
    for c in pc:
        pivmask |= 1 << c
    NP = ((1 << N) - 1) ^ pivmask
    orRep = 0
    for t in range(len(RR)):
        if RR[t] & NP:
            orRep |= 1 << t
    basis = [0] * 30
    bmask = [0] * 30
    mem0 = []
    pv = []
    flipany = tw1 = tw2 = on1 = on2 = 0
    for t in range(len(RR)):
        c = pc[t]
        l = L[c]
        r = R[c]
        d = l ^ r
        k = d.bit_length() - 1
        o = ~d & ((1 << k) - 1)
        mem0.append((t, o, r))
        flipany |= o
        x = d
        m = 1 << t
        while x:
            p = x.bit_length() - 1
            bp = basis[p]
            if bp:
                x ^= bp
                m ^= bmask[p]
            else:
                basis[p] = x
                bmask[p] = m
                pv.append(p)
                break
    Kgt = [0] * 30
    acc = 0
    for p in range(K, -1, -1):
        Kgt[p] = acc
        if acc:
            bit = 1 << p
            tw = Rc[p] & ~Lc[p] & acc
            if tw:
                tw1 |= bit
                if tw & (tw - 1):
                    tw2 |= bit
            os_ = ~Dc[p] & acc & NP
            if os_:
                on1 |= bit
                if os_ & (os_ - 1):
                    on2 |= bit
        acc |= Dc[p]

    def helper(ctx, b, ta, tb, nn):
        excl = 0
        target = 0
        if nn:
            j = (~Dc[b] & Kgt[b] & NP).bit_length() - 1
            excl = 1 << j
            if (R[j] >> b) & 1:
                target = ((RR[ta] >> j) & 1) | (((RR[tb] >> j) & 1) << 1)
        A = RR[ta] & NP & ~excl
        g = 1
        if ta == tb:
            if target:
                target = 1
            if A:
                g |= 2
            return g, target
        B = RR[tb] & NP & ~excl
        if A & ~B:
            g |= 2
        if B & ~A:
            g |= 4
        if A & B:
            g |= 8
        return g, target

    flipany |= tw1 | on1
    return core(X0, K, basis, bmask, mem0, orRep, tw1, tw2, on1, on2, helper, None, flipany, pv)


def main():
    data = sys.stdin.buffer.read().split()
    vals = list(map(int, data))
    T = vals[0]
    pos = 1
    out = []
    for _ in range(T):
        n = vals[pos]
        pos += 1
        if n == 1:
            out.append(vals[pos + 1])
            pos += 2
            continue
        L = vals[pos:pos + n]
        pos += n
        R = vals[pos:pos + n]
        pos += n
        if n >= 150 and array('I').itemsize == 4:
            out.append(solve_big(n, L, R))
        else:
            out.append(solve_small(L, R))
    sys.stdout.write("\n".join(map(str, out)) + "\n")


main()
