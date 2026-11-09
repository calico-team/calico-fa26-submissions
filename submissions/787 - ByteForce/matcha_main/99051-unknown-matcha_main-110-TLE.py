import sys

try:
    import numpy as np
except Exception:
    np = None

if hasattr(int, "bit_count"):
    def pc(x): return x.bit_count()
else:
    def pc(x): return bin(x).count("1")


def consistent(eqs):
    basis = []
    for v, r in eqs:
        for bv, br in basis:
            if v & (bv & -bv):
                v ^= bv
                r ^= br
        if v == 0:
            if r:
                return False
            continue
        basis.append((v, r))
    return True


def small_case(Lv, Rv, B):
    # brute force over endpoint choices (few non-constant intervals)
    m = len(Lv)
    info = []
    for i in range(m):
        d = Lv[i] ^ Rv[i]
        low = (1 << (d.bit_length() - 1)) - 1
        info.append((Lv[i], Rv[i], (~Lv[i]) & low, Rv[i] & low))
    best = 0
    B0 = B
    for l in Lv:
        B0 ^= l
    for xs in range(1 << m):
        T = B0
        ones = twos = 0
        for i in range(m):
            l, r, m0, m1 = info[i]
            if (xs >> i) & 1:
                T ^= r
                mm = m1
            else:
                T ^= l
                mm = m0
            twos |= ones & mm
            ones |= mm
        mask = ((~T) & ones) | (T & twos)
        res = (T | ((1 << mask.bit_length()) - 1)) if mask else T
        if res > best:
            best = res
    return best


def build_rows(vals, top):
    """rows[b] = bitset over variables of bit b of vals[i], b in 0..top"""
    m = len(vals)
    if np is not None and m >= 128:
        arr = np.array(vals, dtype=np.int64)
        rows = []
        for b in range(top + 1):
            bits = ((arr >> b) & 1).astype(np.uint8)
            rows.append(int.from_bytes(np.packbits(bits, bitorder='little').tobytes(), 'little'))
        return rows
    rows = [0] * (top + 1)
    for i in range(m):
        bit = 1 << i
        v = vals[i]
        while v:
            lb = v & -v
            rows[lb.bit_length() - 1] |= bit
            v ^= lb
    return rows


def solve_case(L, R):
    n = len(L)
    B = 0
    Lv = []
    Rv = []
    for i in range(n):
        B ^= L[i]
        if L[i] != R[i]:
            Lv.append(L[i])
            Rv.append(R[i])
    m = len(Lv)
    if m == 0:
        return B
    if m <= 3:
        return small_case(Lv, Rv, B)

    D = [Lv[i] ^ Rv[i] for i in range(m)]
    smax = max(D).bit_length() - 1
    top = smax
    mask_top = (1 << (top + 1)) - 1
    Dr = build_rows(D, top)
    Lr = build_rows([x & mask_top for x in Lv], top)
    E = [0] * (top + 2)
    for i in range(m):
        E[D[i].bit_length() - 1] |= 1 << i
    # act[b] = variables with s > b
    act = [0] * (top + 1)
    cur = 0
    for b in range(top, -1, -1):
        act[b] = cur
        cur |= E[b]

    pivs = []
    rowv = []
    rowr = []
    Pm = 0
    prefix = B >> (top + 1)

    for b in range(top, -1, -1):
        a = Dr[b]
        vec = a
        cst = 0
        for k in range(len(pivs)):
            if (vec >> pivs[k]) & 1:
                vec ^= rowv[k]
                cst ^= rowr[k]
        Bb = (B >> b) & 1
        ac = act[b]
        if ac:
            Lb = Lr[b]
            Rb = Lb ^ a
            Am = ac & a & Rb
            Cm = ac & Lb & Rb
            Bm = ac & ~(Lb | Rb)
            BC = Bm | Cm
            nA = pc(Am)
            if nA or BC:
                ok = False
                if E[b]:
                    if nA:
                        ok = True
                    else:
                        F1 = F0 = 0
                        for k in range(len(pivs)):
                            if rowv[k] == (1 << pivs[k]):
                                if rowr[k]:
                                    F1 |= rowv[k]
                                else:
                                    F0 |= rowv[k]
                        if (Bm & ~F1) or (Cm & ~F0):
                            ok = True
                elif nA >= 2:
                    ok = True
                else:
                    psi = vec
                    FC = BC & ~Pm
                    pcand = []
                    for k in range(len(pivs)):
                        p = pivs[k]
                        if (BC >> p) & 1:
                            v = 0 if (Bm >> p) & 1 else 1
                            pcand.append((rowv[k] ^ (1 << p), v ^ rowr[k]))
                    for tau in (0, 1):
                        r = 1 + tau - nA
                        beta = tau ^ Bb ^ cst
                        if r <= 0:
                            if psi or beta == 0:
                                ok = True
                        elif not BC:
                            pass
                        elif r == 1:
                            for f, al in pcand:
                                if consistent([(f, al), (psi, beta)]):
                                    ok = True
                                    break
                            if not ok and FC:
                                if psi == 0:
                                    ok = (beta == 0)
                                elif psi & (psi - 1) == 0:
                                    if FC & ~psi:
                                        ok = True
                                    else:
                                        i = psi.bit_length() - 1
                                        vi = 0 if (Bm >> i) & 1 else 1
                                        ok = (beta == vi)
                                else:
                                    ok = True
                        else:
                            reps = list(pcand)
                            spec = 0
                            if pc(psi) <= 2:
                                spec |= psi & FC
                            if FC:
                                for f, al in pcand:
                                    if f and f & (f - 1) == 0:
                                        spec |= f & FC
                                    x = f ^ psi
                                    if x and x & (x - 1) == 0:
                                        spec |= x & FC
                                gen = FC & ~spec
                                t = spec
                                while t:
                                    lb = t & -t
                                    t ^= lb
                                    i = lb.bit_length() - 1
                                    reps.append((lb, 0 if (Bm >> i) & 1 else 1))
                                for _ in range(3):
                                    if not gen:
                                        break
                                    lb = gen & -gen
                                    gen ^= lb
                                    i = lb.bit_length() - 1
                                    reps.append((lb, 0 if (Bm >> i) & 1 else 1))
                            lr = len(reps)
                            for x in range(lr):
                                for y in range(x + 1, lr):
                                    if consistent([reps[x], reps[y], (psi, beta)]):
                                        ok = True
                                        break
                                if ok:
                                    break
                        if ok:
                            break
                if ok:
                    return (prefix << (b + 1)) | ((1 << (b + 1)) - 1)
        if vec == 0:
            bit = Bb ^ cst
        else:
            bit = 1
            rhs = 1 ^ Bb ^ cst
            q = (vec & -vec).bit_length() - 1
            for k in range(len(pivs)):
                if (rowv[k] >> q) & 1:
                    rowv[k] ^= vec
                    rowr[k] ^= rhs
            pivs.append(q)
            rowv.append(vec)
            rowr.append(rhs)
            Pm |= 1 << q
        prefix = (prefix << 1) | bit
    return prefix


def main():
    data = sys.stdin.buffer.read().split()
    t = int(data[0]); pos = 1
    out = []
    for _ in range(t):
        n = int(data[pos]); pos += 1
        L = list(map(int, data[pos:pos + n])); pos += n
        R = list(map(int, data[pos:pos + n])); pos += n
        out.append(solve_case(L, R))
    sys.stdout.write("\n".join(map(str, out)) + "\n")


if __name__ == "__main__":
    main()
