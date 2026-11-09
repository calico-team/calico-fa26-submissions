import sys
from collections import deque

def hal():
    dd = sys.stdin.read().split()
    if not dd:
        return

    tt = int(dd[0])
    prr = 1

    for _ in range(tt):
        n = int(dd[prr])
        m = int(dd[prr + 1])
        k = int(dd[prr + 2])
        prr += 3

        pr = [0] + [int(x) for x in dd[prr:prr+n]]
        prr += n

        bace = {i: [] for i in range(n+1)}
        rq = [0] * (n+1)

        for i in range(1, n+1):
            p = pr[i]
            if p != 0:
                bace[p].append(i)
                rq[i] += 1

        tayar = deque()

        for i in range(1, n+1):
            if rq[i] == 0:
                tayar.append(i)

        ann = 0

        for sem in range(m):
            if not tayar:
                break

            ct = []

            while tayar and len(ct) < k:
                cur = tayar.popleft()
                ct.append(cur)

            ann += len(ct)

            for cur in ct:
                for aga in bace[cur]:
                    rq[aga] -= 1

                    if rq[aga] == 0:
                        tayar.append(aga)

        print(ann)


if __name__ == "__main__":
    hal()