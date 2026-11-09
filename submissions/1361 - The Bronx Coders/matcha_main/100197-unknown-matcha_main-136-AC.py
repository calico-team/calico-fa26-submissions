import sys
import random


def solve(n, ls, rs):
    rnd = random.getrandbits
    A = 0
    v = [0] * 31
    expr = [0] * 31
    owner = [-1] * 31
    ds = [0] * n
    hl = 0
    for i in range(n):
        l = ls[i]
        r = rs[i]
        A ^= l
        d = l ^ r
        ds[i] = d
        if r - l + 1 > hl:
            hl = r - l + 1
        x = d
        e = 0
        while x:
            t = x.bit_length() - 1
            if v[t]:
                x ^= v[t]
                e ^= expr[t]
            else:
                v[t] = x
                expr[t] = e | (1 << t)
                owner[t] = i
                break
    slots = [s for s in range(30, -1, -1) if v[s]]
    is_slot = [False] * n
    for s in slots:
        is_slot[owner[s]] = True
    M = A
    for s in slots:
        if (M ^ v[s]) > M:
            M ^= v[s]
    gmax = hl.bit_length() - 1
    if gmax <= 0:
        return M

    full = (1 << 31) - 1
    rand = [rnd(62) | 1 for _ in range(n)]
    U = [0] * 31
    used = [0] * n
    fl0 = [0] * n
    fl1 = [0] * n
    fr0 = [0] * n
    fr1 = [0] * n
    one_any = two_any = one_f = two_f = one_k = two_k = 0
    for i in range(n):
        l = ls[i]
        r = rs[i]
        d = ds[i]
        x = d
        u = 0
        rk = rand[i]
        while x:
            t = x.bit_length() - 1
            x ^= v[t]
            u |= 1 << t
            U[t] ^= rk
        used[i] = u
        tzl = (l & -l).bit_length() - 1 if l else 31
        lowl = (1 << (tzl + 1)) - 1
        r1 = r + 1
        tor = (r1 & -r1).bit_length() - 1
        lowr = (1 << (tor + 1)) - 1
        if d:
            m = d.bit_length() - 1
            below = (1 << m) - 1
            a = ((~l) & below) | ((1 << m) if tor >= m else 0)
            b = (r & below) | ((1 << m) if tzl >= m else 0)
            c0 = lowl & ((1 << (m + 1)) - 1) | (lowl & lowr & ~1 << (m + 1) - 1)
            c1 = lowr & ((1 << (m + 1)) - 1) | (lowl & lowr & ~1 << (m + 1) - 1)
        else:
            a = b = 0
            c0 = c1 = lowl & lowr
        fl1[i] = a
        fr1[i] = b
        fl0[i] = c0 & full
        fr0[i] = c1 & full
        if not is_slot[i]:
            f = a | b
            k = (c0 | c1) & full
            y = f | k
            two_any |= one_any & y
            one_any |= y
            two_f |= one_f & f
            one_f |= f
            two_k |= one_k & k
            one_k |= k

    star = A ^ M
    x = star
    star_used = 0
    while x:
        t = x.bit_length() - 1
        x ^= v[t]
        star_used |= 1 << t

    def opts(i, p, g):
        if p == 0:
            return ((fl0[i] >> g) & 1, (fl1[i] >> g) & 1)
        return ((fr0[i] >> g) & 1, (fr1[i] >> g) & 1)

    def consistent(eqs):
        k = len(eqs)
        for mask in range(1, 1 << k):
            h = 0
            c = 0
            for j in range(k):
                if mask >> j & 1:
                    h ^= eqs[j][0]
                    c ^= eqs[j][1]
            if h == 0 and c:
                return False
        return True

    def rep_of(u, g):
        e = 0
        for s in slots:
            if s <= g:
                break
            if u >> s & 1:
                e ^= expr[s]
        return e

    anymask = one_any
    for o in owner:
        if o >= 0:
            anymask |= fl0[o] | fl1[o] | fr0[o] | fr1[o]

    for g in range(gmax, -1, -1):
        bit = 1 << g
        if not anymask & bit:
            continue
        mg = (M >> g) & 1
        bhi = [s for s in slots if s > g]
        cm = rep_of(star_used, g)
        e = A
        for b in bhi:
            if cm >> b & 1:
                e ^= ds[owner[b]]
        beta0 = (e >> g) & 1

        n_any = 2 if two_any & bit else (1 if one_any & bit else 0)
        n_f = 2 if two_f & bit else (1 if one_f & bit else 0)
        n_k = 1 if one_k & bit else 0
        r1 = 0
        k0 = owner[g] if v[g] else -1
        k0_any = False
        slot_flip = []
        for s in slots:
            if s > g:
                continue
            o = owner[s]
            a0 = (fl0[o] >> g) & 1
            a1 = (fl1[o] >> g) & 1
            b0 = (fr0[o] >> g) & 1
            b1 = (fr1[o] >> g) & 1
            anyo = a0 or a1 or b0 or b1
            if anyo:
                n_any += 1
            if a1 or b1:
                n_f += 1
                slot_flip.append(o)
            if a0 or b0:
                n_k += 1
            if used[o] >> g & 1:
                r1 += 1
            if o == k0:
                k0_any = anyo
        bits = set()
        if r1 >= 2:
            if n_any >= 1:
                bits.update((0, 1))
        elif r1 == 1:
            if n_any - (1 if k0_any else 0) >= 1:
                bits.update((0, 1))
            for p in (0, 1):
                k_, f_ = opts(k0, p, g)
                if k_:
                    bits.add(beta0 ^ p)
                if f_:
                    bits.add(beta0 ^ p ^ 1)
        else:
            if n_f >= 1:
                bits.add(beta0 ^ 1)
            if n_k >= 1:
                bits.add(beta0)
            if n_f >= 2:
                bits.add(beta0)
        if 1 in bits:
            return ((M >> (g + 1)) << (g + 1)) | (bit << 1) - 1

        if bhi:
            ufree = U[:]
            for s2 in bhi:
                o = owner[s2]
                u = used[o]
                ro = rand[o]
                for s in slots:
                    if u >> s & 1:
                        ufree[s] ^= ro
            h = {}
            for b in bhi:
                hv = 0
                for s in bhi:
                    if expr[s] >> b & 1:
                        hv ^= ufree[s]
                h[b] = hv
            hb = ufree[g] if v[g] else 0
            cb = {b: (cm >> b) & 1 for b in bhi}

            for b in bhi:
                o = owner[b]
                hx = h[b]
                cx = cb[b]
                for p in (0, 1):
                    if p == 0:
                        k_ = (fl0[o] >> g) & 1
                        f_ = (fl1[o] >> g) & 1
                    else:
                        k_ = (fr0[o] >> g) & 1
                        f_ = (fr1[o] >> g) & 1
                    if not (k_ or f_):
                        continue
                    if hx == 0:
                        if cx != p:
                            continue
                        bm = 3 if hb else 1 << beta0
                    elif hb == 0:
                        bm = 1 << beta0
                    elif hx == hb:
                        bm = 1 << (beta0 ^ p ^ cx)
                    else:
                        bm = 3
                    if k_:
                        if bm & 2:
                            bits.add(1)
                        if bm & 1:
                            bits.add(0)
                    if f_:
                        if bm & 1:
                            bits.add(1)
                        if bm & 2:
                            bits.add(0)
                if 1 in bits:
                    break
            if 1 not in bits:
                cands = []
                if r1 == 1 and n_any - (1 if k0_any else 0) == 0:
                    cands = [k0]
                elif r1 == 0 and n_f == 1:
                    if slot_flip:
                        cands = slot_flip[:1]
                    else:
                        for i in range(n):
                            if not is_slot[i] and ((fl1[i] | fr1[i]) >> g) & 1:
                                cands = [i]
                                break
                for i in cands:
                    ri = (used[i] >> g) & 1
                    rep = rep_of(used[i], g)
                    rr = rand[i]
                    hb2 = hb ^ (rr if ri else 0)
                    for p in (0, 1):
                        if not opts(i, p, g)[1]:
                            continue
                        b0 = beta0 ^ (ri & p)
                        for b in bhi:
                            o = owner[b]
                            a_ = (rep >> b) & 1
                            hh = h[b] ^ (rr if a_ else 0)
                            rhs0 = cb[b] ^ (a_ & p)
                            for q in (0, 1):
                                if not opts(o, q, g)[1]:
                                    continue
                                for beta in (0, 1):
                                    if beta in bits:
                                        continue
                                    if consistent([(hh, q ^ rhs0), (hb2, beta ^ b0)]):
                                        bits.add(beta)
            if 1 not in bits:
                fl = []
                for b in bhi:
                    o = owner[b]
                    for q in (0, 1):
                        if opts(o, q, g)[1]:
                            fl.append((b, q))
                for x1 in range(len(fl)):
                    b1, q1 = fl[x1]
                    for x2 in range(x1 + 1, len(fl)):
                        b2, q2 = fl[x2]
                        if b1 == b2:
                            continue
                        for beta in (0, 1):
                            if beta in bits:
                                continue
                            if consistent([(h[b1], q1 ^ cb[b1]), (h[b2], q2 ^ cb[b2]), (hb, beta ^ beta0)]):
                                bits.add(beta)

        if 1 in bits:
            return ((M >> (g + 1)) << (g + 1)) | (bit << 1) - 1
        if bits and mg == 0:
            return ((M >> (g + 1)) << (g + 1)) | (bit - 1)
    return M


def main():
    data = sys.stdin.buffer.read().split()
    t = int(data[0])
    pos = 1
    out = []
    for _ in range(t):
        n = int(data[pos])
        pos += 1
        ls = [int(x) for x in data[pos:pos + n]]
        pos += n
        rs = [int(x) for x in data[pos:pos + n]]
        pos += n
        out.append(str(solve(n, ls, rs)))
    sys.stdout.write("\n".join(out) + "\n")


main()