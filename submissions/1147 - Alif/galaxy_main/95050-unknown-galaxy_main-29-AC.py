import sys

def main():
    d = sys.stdin.read().split()
    p = 0
    T = int(d[p]); p += 1
    res = []
    for _ in range(T):
        N, M, Q = int(d[p]), int(d[p+1]), int(d[p+2])
        p += 3
        g = d[p:p+N]
        p += N

        C = N * M
        ok = [[False] * C, [False] * C]   # ok[mode][cell]

        for r in range(N):
            row = g[r]
            for c in range(M):
                i = r * M + c
                ch = row[c]
                if ch == '.':
                    ok[0][i] = True
                    ok[1][i] = True
                elif ch == 'B':
                    ok[0][i] = True
                else:
                    ok[1][i] = True

        par = list(range(2 * C))

        def find(x):
            while par[x] != x:
                par[x] = par[par[x]]
                x = par[x]
            return x

        def uni(a, b):
            ra, rb = find(a), find(b)
            if ra != rb:
                par[ra] = rb

        # normal tile -> its two color states are the same place
        for i in range(C):
            if ok[0][i] and ok[1][i]:
                uni(2 * i, 2 * i + 1)

        # neighbors in the same mode
        for r in range(N):
            for c in range(M):
                u = r * M + c
                if c + 1 < M:
                    v = u + 1
                    for m in (0, 1):
                        if ok[m][u] and ok[m][v]:
                            uni(2 * u + m, 2 * v + m)
                if r + 1 < N:
                    v = u + M
                    for m in (0, 1):
                        if ok[m][u] and ok[m][v]:
                            uni(2 * u + m, 2 * v + m)

        for _ in range(Q):
            rs = int(d[p]); cs = int(d[p+1]); re = int(d[p+2]); ce = int(d[p+3])
            p += 4
            s = rs * M + cs
            e = re * M + ce
            root = find(2 * s)
            hit = (ok[0][e] and find(2 * e) == root) or (ok[1][e] and find(2 * e + 1) == root)
            res.append("YES" if hit else "NO")

    sys.stdout.write("\n".join(res))

if __name__ == "__main__":
    main()