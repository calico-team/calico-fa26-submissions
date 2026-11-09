import sys
from array import array
from math import isqrt


def solve() -> None:
    tkns = list(map(int, sys.stdin.buffer.read().split()))
    if not tkns:
        return

    tkn_i = 0
    tst_cass = tkns[tkn_i]
    tkn_i += 1
    otpt = []

    for _ in range(tst_cass):
        n, m, q = tkns[tkn_i : tkn_i + 3]
        tkn_i += 3

        ertqaks = []
        for _ in range(q):
            r, c, pwr = tkns[tkn_i : tkn_i + 3]
            tkn_i += 3
            ertqaks.append((r, c, pwr))

        trnspsd = n > m
        rs, clms = (m, n) if trnspsd else (n, m)
        strd = clms + 1

        # prnt[cell] is the next unassigned clmn in that row.
        prnt = list(range(rs * strd))
        rdngs = array("q", [0]) * (rs * clms)
        remng = rs * clms

        def find(indx: int) -> int:
            while prnt[indx] != indx:
                prnt[indx] = prnt[prnt[indx]]
                indx = prnt[indx]
            return indx

        for orgnl_r, orgnl_c, pwr in reversed(ertqaks):
            if remng == 0:
                break
            cntr_rw, cntr_clm = (
                (orgnl_c, orgnl_r)
                if trnspsd
                else (orgnl_r, orgnl_c)
            )
            pwr_squrd = pwr * pwr
            frst_rw = max(0, cntr_rw - pwr)
            lst_rw = min(rs - 1, cntr_rw + pwr)

            for row in range(frst_rw, lst_rw + 1):
                rw_dstnc = row - cntr_rw
                hrzntl_rdus = isqrt(pwr_squrd - rw_dstnc * rw_dstnc)
                lft = max(0, cntr_clm - hrzntl_rdus)
                rgt = min(clms - 1, cntr_clm + hrzntl_rdus)

                indx = find(row * strd + lft)
                while indx <= row * strd + rgt:
                    clmn = indx % strd
                    dstnc_squrd = (
                        rw_dstnc * rw_dstnc
                        + (clmn - cntr_clm) * (clmn - cntr_clm)
                    )
                    rdngs[row * clms + clmn] = (
                        pwr_squrd - dstnc_squrd + 1
                    )
                    prnt[indx] = find(indx + 1)
                    indx = prnt[indx]
                    remng -= 1

        if not trnspsd:
            for row in range(rs):
                strt = row * clms
                otpt.append(" ".join(map(str, rdngs[strt : strt + clms])))
        else:
            for row in range(n):
                otpt.append(
                    " ".join(
                        str(rdngs[clmn * clms + row])
                        for clmn in range(rs)
                    )
                )

    sys.stdout.write("\n".join(otpt))


if __name__ == "__main__":
    solve()