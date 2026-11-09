import sys

def go(N, M, grid, qs):
    C = N * M

    ch = [grid[r][c] for r in range(N) for c in range(M)]

    # can[mode][cell] — walkable in blue (0) or red (1)
    can = [[False] * C for _ in range(2)]
    for i in range(C):
        x = ch[i]
        if x == '.':
            can[0][i] = can[1][i] = True
        elif x == 'B':
            can[0][i] = True
        else:
            can[1][i] = True

    nbr = [[] for _ in range(C)]
    for r in range(N):
        for c in range(M):
            u = r * M + c
            if r > 0: nbr[u].append(u - M)
            if r + 1 < N: nbr[u].append(u + M)
            if c > 0: nbr[u].append(u - 1)
            if c + 1 < M: nbr[u].append(u + 1)

    # group by start cell so each BFS runs once
    groups = {}
    for qi, (rs, cs, re, ce, K) in enumerate(qs):
        s = rs * M + cs
        groups.setdefault(s, []).append((qi, re * M + ce, K))

    ans = [None] * len(qs)

    for s, lst in groups.items():
        cap = max(k for _, _, k in lst)

        # state = cell * 2 + mode
        dist = [-1] * (2 * C)
        st0 = 2 * s
        dist[st0] = 0
        layer = [st0]
        d = 0

        # expand only as far as the largest K in this group
        while layer and d < cap:
            nxt = []
            nd = d + 1
            for st in layer:
                cell = st >> 1
                m = st & 1
                if ch[cell] == '.':
                    ns = st ^ 1
                    if dist[ns] < 0:
                        dist[ns] = nd
                        nxt.append(ns)
                ok = can[m]
                for v in nbr[cell]:
                    if ok[v]:
                        ns = (v << 1) | m
                        if dist[ns] < 0:
                            dist[ns] = nd
                            nxt.append(ns)
            layer = nxt
            d = nd

        for qi, e, K in lst:
            best = -1
            d0 = dist[2 * e]
            d1 = dist[2 * e + 1]
            if can[0][e] and d0 >= 0:
                best = d0
            if can[1][e] and d1 >= 0 and (best < 0 or d1 < best):
                best = d1
            ans[qi] = "YES" if 0 <= best <= K else "NO"

    return ans

def main():
    d = sys.stdin.buffer.read().split()
    p = 0
    T = int(d[p]); p += 1
    out = []
    for _ in range(T):
        N = int(d[p]); M = int(d[p+1]); Q = int(d[p+2])
        p += 3
        grid = [d[p+i].decode() for i in range(N)]
        p += N
        qs = []
        for _ in range(Q):
            rs = int(d[p]); cs = int(d[p+1]); re = int(d[p+2]); ce = int(d[p+3]); K = int(d[p+4])
            p += 5
            qs.append((rs, cs, re, ce, K))
        out.extend(go(N, M, grid, qs))
    sys.stdout.write("\n".join(out) + "\n")

if __name__ == "__main__":
    main()