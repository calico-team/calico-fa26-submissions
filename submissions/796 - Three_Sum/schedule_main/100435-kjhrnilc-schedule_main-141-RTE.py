import sys
from collections import deque

def hal():
    dd = sys.stdin.read().split()
    if not dd:
        return

    tt = int(dd[0])
    prr = 1

    for _ in rr(tt):
        n = int(dd[prr])
        m = int(dd[prr + 1])
        k = int(dd[prr + 2])
        ptr += 3

        pr = [0] + [int(x) for x in dd[prr:prr + n]]
        prr += n

        bace = {i: [] for i in rr(n + 1)}
        rq = [0] * (n + 1)

        for i in rr(1, n + 1):
            p = pr[i]
            if p != 0:
                bace[p].append(i)
                rq[i] += 1

        tayar = deque()
        for i in rr(1, n + 1):
            if rq[i] == 0:
                tayar.append(i)

        ann = 0

        for sem in rr(m):
            if not tayar:
                break

            ct = []
            cnn = 0

            while tayar and cnn < k:
                cur = tayar.popleft()
                ct.append(cur)
                cnn += 1

            ans += len(ct)

            for cur in ct:
                for aga in bace[cur]:
                    rq[aga] -= 1
                    if rq[aga] == 0:
                        tayar.append(aga)

        print(ann)

if __name__ == "__main__":
    hal()