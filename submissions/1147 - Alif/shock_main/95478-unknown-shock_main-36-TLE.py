import sys

def go(N, M, qs):
    g = [[0] * M for _ in range(N)]
    nxt = [list(range(M + 1)) for _ in range(N)]

    def find(r, c):
        par = nxt[r]
        root = c
        while par[root] != root:
            root = par[root]
        while par[c] != root:
            par[c], c = root, par[c]
        return root

    for R, C, P in reversed(qs):
        P2 = P * P
        for r in range(max(0, R - P), min(N, R + P + 1)):
            dr = r - R
            half = P2 - dr * dr
            if half < 0:
                continue
            w = int(half ** 0.5)
            while w * w > half:
                w -= 1
            while (w + 1) * (w + 1) <= half:
                w += 1
            lo = max(0, C - w)
            hi = min(M - 1, C + w)
            if lo > hi:
                continue
            c = find(r, lo)
            while c <= hi:
                g[r][c] = P2 - (dr * dr + (c - C) ** 2) + 1
                nxt[r][c] = c + 1
                c = find(r, c + 1)

    return g

def main():
    d = sys.stdin.read().split()
    p = 0
    T = int(d[p]); p += 1
    res = []
    for _ in range(T):
        N, M, Q = int(d[p]), int(d[p+1]), int(d[p+2])
        p += 3
        qs = []
        for _ in range(Q):
            R = int(d[p]); C = int(d[p+1]); P = int(d[p+2])
            p += 3
            qs.append((R, C, P))
        g = go(N, M, qs)
        for row in g:
            res.append(" ".join(map(str, row)))
    sys.stdout.write("\n".join(res) + "\n")

if __name__ == "__main__":
    main()