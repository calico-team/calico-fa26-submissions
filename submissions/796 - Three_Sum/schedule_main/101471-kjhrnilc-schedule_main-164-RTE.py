
import sys
import heapq

def hal():
    dd = sys.stdin.read().split()
    if not dd:
        return

    tt = int(dd[0])
    prr = 1

    for _ in range(tt):
        n, m, k = map(int, dd[prr:prr+3])
        prr += 3

        pr = [0] + list(map(int, dd[prr:prr+n]))
        prr += n

        bace = [[] for _ in range(n+1)]
        rq = [0] * (n+1)

        for i in range(1, n+1):
            if pr[i] != 0:
                bace[pr[i]].append(i)
                rq[i] += 1

        qq = []
        for i in range(1, n+1):
            if rq[i] == 0:
                qq.append(i)

        hat = [1] * (n+1)
        ordd = list(qq)

        for xx in ordd:
            for yy in bace[xx]:
                ordd.append(yy)

        for xx in reversed(ordd):
            for yy in bace[xx]:
                hat[xx] = max(hat[xx], hat[yy] + 1)

        tayar = []

        for i in range(1, n+1):
            if rq[i] == 0:
                heapq.heappush(tayar, (-hat[i], i))

        ann = 0

        for _ in range(m):
            ct = []

            for _ in range(k):
                if tayar:
                    ct.append(heapq.heappop(tayar)[1])

            if not ct:
                break

            ann += len(ct)

            for cur in ct:
                for aga in bace[cur]:
                    rq[aga] -= 1

                    if rq[aga] == 0:
                        heapq.heappush(tayar, (-hat[aga], aga))

        print(ann)


if __name__ == "__main__":
    hal()