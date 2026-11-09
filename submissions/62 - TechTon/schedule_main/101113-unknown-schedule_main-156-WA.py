import heapq
import sys


def mximm_crss(n, smstrs, cpcty, prreqsts):
    chldrn = [[] for _ in range(n)]
    rts = []

    for crs, prreqst in enumerate(prreqsts):
        if prreqst == 0:
            rts.append(crs)
        else:
            chldrn[prreqst - 1].append(crs)

    rmnng_chldrn = [len(crs_chldrn) for crs_chldrn in chldrn]
    dstnc = [0] * n
    stk = list(range(n))

    while stk:
        crs = stk.pop()
        if rmnng_chldrn[crs] != 0:
            continue

        prnt = prreqsts[crs] - 1
        if prnt >= 0:
            dstnc[prnt] = max(dstnc[prnt], dstnc[crs] + 1)
            rmnng_chldrn[prnt] -= 1
            if rmnng_chldrn[prnt] == 0:
                stk.append(prnt)

    avlbl = [(-dstnc[crs], crs) for crs in rts]
    heapq.heapify(avlbl)

    cmpltd = 0
    for _ in range(smstrs):
        if not avlbl:
            break

        crnt_smstr = []
        for _ in range(cpcty):
            if not avlbl:
                break
            _, crs = heapq.heappop(avlbl)
            crnt_smstr.append(crs)

        cmpltd += len(crnt_smstr)
        for crs in crnt_smstr:
            for child in chldrn[crs]:
                heapq.heappush(avlbl, (-dstnc[child], child))

    return cmpltd


def main():
    deta = list(map(int, sys.stdin.buffer.read().split()))
    if not deta:
        return

    tst_cass = deta[0]
    pstn = 1
    ansrs = []

    for _ in range(tst_cass):
        n, smstrs, cpcty = deta[pstn:pstn + 3]
        pstn += 3
        prreqsts = deta[pstn:pstn + n]
        pstn += n
        ansrs.append(str(mximm_crss(n, smstrs, cpcty, prreqsts)))

    sys.stdout.write("\n".join(ansrs) + "\n")


if __name__ == "__main__":
    main()