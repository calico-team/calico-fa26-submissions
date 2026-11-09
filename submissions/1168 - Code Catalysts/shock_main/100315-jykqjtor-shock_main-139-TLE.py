import sys
from math import isqrt


def solve(N, M, Q, earthquakes):
    W = M + 1
    nxt = list(range(N * W))
    res = [0] * (N * W)
    rowrem = [M] * N
    remaining = N * M
    wcache = {}

    def find(i):
        root = i
        while nxt[root] != root:
            root = nxt[root]
        while nxt[i] != root:
            nxt[i], i = root, nxt[i]
        return root

    for R, C, P in reversed(earthquakes):
        if remaining == 0:
            break
        ws = wcache.get(P)
        if ws is None:
            pp0 = P * P
            ws = [isqrt(pp0 - d * d) for d in range(P + 1)]
            wcache[P] = ws
        pp = P * P
        for r in range(R - P, R + P + 1):
            if rowrem[r] == 0:
                continue
            dr = r - R
            if dr < 0:
                w = ws[-dr]
            else:
                w = ws[dr]
            rem = pp - dr * dr
            center = r * W + C
            hi = center + w
            i = center - w
            if nxt[i] != i:
                i = find(i)
            cnt = 0
            while i <= hi:
                dc = i - center
                res[i] = rem - dc * dc + 1
                cnt += 1
                j = i + 1
                if nxt[j] != j:
                    j = find(j)
                nxt[i] = j
                i = j
            if cnt:
                rowrem[r] -= cnt
                remaining -= cnt

    return [res[r * W:r * W + M] for r in range(N)]


def main():
    data = sys.stdin.buffer.read().split()
    p = 0
    T = int(data[p])
    p += 1
    out = []
    for _ in range(T):
        N = int(data[p])
        M = int(data[p + 1])
        Q = int(data[p + 2])
        p += 3
        earthquakes = []
        for _ in range(Q):
            earthquakes.append((int(data[p]), int(data[p + 1]), int(data[p + 2])))
            p += 3
        answer = solve(N, M, Q, earthquakes)
        for row in answer:
            out.append(' '.join(map(str, row)))
    sys.stdout.write('\n'.join(out) + '\n')


if __name__ == '__main__':
    main()