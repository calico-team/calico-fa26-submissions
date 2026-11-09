import sys

def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    it = iter(data)
    t = next(it, 0)
    out = []
    for _ in range(t):
        n = next(it)
        L = [next(it) for _ in range(n)]
        R = [next(it) for _ in range(n)]

        # ---------- small N : exact linear system ----------
        if n <= 30:
            p = []
            for i in range(n):
                d = L[i] ^ R[i]
                p.append(d.bit_length() - 1 if d else -1)
            # M[b] : bit i = coeff of s_i in equation b
            M = [0] * 30
            C = [0] * 30
            for b in range(30):
                mask = 0
                c = 0
                for i in range(n):
                    lb = (L[i] >> b) & 1
                    rb = (R[i] >> b) & 1
                    if p[i] == b:
                        mask |= (1 << i)
                    elif p[i] > b:
                        c ^= lb
                        if lb != rb:
                            mask |= (1 << i)
                    else:
                        c ^= lb
                M[b] = mask
                C[b] = c

            basis = {}

            def try_add(bd, mask, rhs):
                nd = dict(bd)
                m, r = mask, rhs
                while m:
                    lead = m.bit_length() - 1
                    if lead in nd:
                        bm, br = nd[lead]
                        m ^= bm
                        r ^= br
                    else:
                        break
                if m == 0:
                    return nd, (r == 0)
                nd[m.bit_length() - 1] = (m, r)
                return nd, True

            def can_set(bd, mask, rhs):
                m, r = mask, rhs
                while m:
                    lead = m.bit_length() - 1
                    if lead in bd:
                        bm, br = bd[lead]
                        m ^= bm
                        r ^= br
                    else:
                        break
                if m == 0:
                    return r == 0
                return True

            ans = 0
            done = False
            for b in range(29, -1, -1):
                if done:
                    break

                def check_free(desired):
                    nb, ok = try_add(basis, M[b], desired ^ C[b] ^ 1)
                    if not ok:
                        return False
                    cand = []
                    for i in range(n):
                        if p[i] > b:
                            if ((L[i] >> b) & 1) == 0 or ((R[i] >> b) & 1) == 1:
                                cand.append(i)
                    if len(cand) > len(nb):
                        return True
                    for i in cand:
                        vals = []
                        if ((L[i] >> b) & 1) == 0:
                            vals.append(0)
                        if ((R[i] >> b) & 1) == 1:
                            vals.append(1)
                        for v in vals:
                            if can_set(nb, 1 << i, v):
                                return True
                    return False

                if check_free(1):
                    ans |= (1 << b)
                    ans |= (1 << b) - 1
                    done = True
                    break
                nb1, ok1 = try_add(basis, M[b], 1 ^ C[b])
                if ok1:
                    ans |= (1 << b)
                    basis = nb1
                    continue
                if check_free(0):
                    ans |= (1 << b) - 1
                    done = True
                    break
                nb0, ok0 = try_add(basis, M[b], 0 ^ C[b])
                if ok0:
                    basis = nb0
            out.append(str(ans))
            continue

        # ---------- large N : max xor of C_i + one free ----------
        B = 0
        for x in L:
            B ^= x
        # linear basis of C_i (30 bits)
        bas = [0] * 30
        p_list = []
        for i in range(n):
            d = L[i] ^ R[i]
            pi = d.bit_length() - 1 if d else -1
            p_list.append(pi)
            if pi == -1:
                ci = 0
            else:
                ci = (1 << pi) | (d & ((1 