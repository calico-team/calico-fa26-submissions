try:
    popcount = int.bit_count
except AttributeError:
    def popcount(x):
        return bin(x).count('1')


def consistent(m1, r1, m2, r2):
    if m1 == 0 and r1:
        return False
    if m2 == 0 and r2:
        return False
    if m1 == m2 and r1 != r2:
        return False
    return True


def solve(N: int, L: list[int], R: list[int]) -> int:
    X = 0
    top = -1

    for l, r in zip(L, R):
        X ^= l
        d = (l ^ r).bit_length() - 1
        if d > top:
            top = d

    if top < 0:
        return X

    w = top + 1
    wmask = (1 << w) - 1
    c = (X >> w) << w
    fmt = '0%db' % w

    Lcols = zip(*[format(l & wmask, fmt) for l in L])
    Rcols = zip(*[format(r & wmask, fmt) for r in R])

    active = 0
    piv = []
    pivmask = 0

    for b in range(top, -1, -1):
        Lb = int(''.join(next(Lcols)), 2)
        Rb = int(''.join(next(Rcols)), 2)

        col = Lb ^ Rb
        kappa = popcount(Lb) & 1
        rho = col

        for p in piv:
            if rho & p[0]:
                rho ^= p[0] ^ p[1]
                kappa ^= p[2]

        if active:
            U = active & ~(Lb & col)

            if U:
                Ufree = U & ~pivmask

                if popcount(Ufree) >= 2:
                    return ((c >> (b + 1)) << (b + 1)) | ((1 << (b + 1)) - 1)

                desc = []

                if Ufree:
                    desc.append((Ufree, 0, Ufree))

                for p in piv:
                    if U & p[0]:
                        desc.append((p[1], p[2], p[0]))

                opts = []

                for form, const, eb in desc:
                    if eb & Lb:
                        opts.append((1,))
                    elif eb & Rb:
                        opts.append((0, 1))
                    else:
                        opts.append((0,))

                fin = False

                for (form, const, eb), o in zip(desc, opts):
                    for v in o:
                        if consistent(form, v ^ const, rho, kappa):
                            fin = True
                            break
                    if fin:
                        break

                if not fin:
                    nd = len(desc)

                    for i in range(nd):
                        fi, ci, _ = desc[i]

                        for j in range(i + 1, nd):
                            fj, cj, _ = desc[j]

                            for vi in opts[i]:
                                for vj in opts[j]:
                                    if consistent(fi, vi ^ ci, fj, vj ^ cj):
                                        fin = True
                                        break
                                if fin:
                                    break
                            if fin:
                                break
                        if fin:
                            break

                if fin:
                    return ((c >> (b + 1)) << (b + 1)) | ((1 << (b + 1)) - 1)

        if rho:
            c |= 1 << b
            q = rho & -rho

            for p in piv:
                if p[1] & q:
                    p[1] ^= rho
                    p[2] ^= 1 ^ kappa

            piv.append([q, rho ^ q, 1 ^ kappa])
            pivmask |= q

        elif kappa:
            c |= 1 << b

        active |= col

    return c


def main():
    T = int(input())

    for _ in range(T):
        N = int(input())
        L = list(map(int, input().split()))
        R = list(map(int, input().split()))

        print(solve(N, L, R))


if __name__ == '__main__':
    main()
