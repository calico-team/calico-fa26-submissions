import sys
 
 
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
        G = [data[p + i].decode() for i in range(N)]
        p += N
        total = 2 * N * M
        valid = [False] * total
        for c in range(M):
            for r in range(N):
                ch = G[r][c]
                base = (c * N + r) * 2
                valid[base] = ch == '.' or ch == 'B'
                valid[base + 1] = ch == '.' or ch == 'R'
        adj = [None] * total
        for c in range(M):
            for r in range(N):
                base = (c * N + r) * 2
                normal = G[r][c] == '.'
                for m in range(2):
                    s = base + m
                    if not valid[s]:
                        continue
                    lst = []
                    if r > 0 and valid[s - 2]:
                        lst.append(s - 2)
                    if r < N - 1 and valid[s + 2]:
                        lst.append(s + 2)
                    if c > 0 and valid[s - 2 * N]:
                        lst.append(s - 2 * N)
                    if c < M - 1 and valid[s + 2 * N]:
                        lst.append(s + 2 * N)
                    if normal:
                        lst.append(s ^ 1)
                    adj[s] = lst
        qs = []
        qe = []
        qcols = []
        qk = []
        for i in range(Q):
            r1 = int(data[p])
            c1 = int(data[p + 1])
            r2 = int(data[p + 2])
            c2 = int(data[p + 3])
            k = int(data[p + 4])
            p += 5
            qs.append((c1 * N + r1) * 2)
            qe.append((c2 * N + r2) * 2)
            qcols.append((c1, c2))
            qk.append(k)
        INF = 1 << 60
        best = [INF] * Q
        stack = [(0, M - 1, list(range(Q)))]
        while stack:
            l, r, qlist = stack.pop()
            if not qlist:
                continue
            mid = (l + r) >> 1
            lo = l * 2 * N
            hi = (r + 1) * 2 * N
            size = hi - lo
            tables = []
            for rr in range(N):
                for m in range(2):
                    src = (mid * N + rr) * 2 + m
                    if not valid[src]:
                        continue
                    dist = [-1] * size
                    dist[src - lo] = 0
                    cur = [src]
                    d = 0
                    while cur:
                        d += 1
                        nxt = []
                        for s in cur:
                            for t in adj[s]:
                                if lo <= t < hi and dist[t - lo] < 0:
                                    dist[t - lo] = d
                                    nxt.append(t)
                        cur = nxt
                    tables.append(dist)
            left = []
            right = []
            for qi in qlist:
                su = qs[qi] - lo
                e0 = qe[qi] - lo
                e1 = e0 + 1
                v0 = valid[qe[qi]]
                v1 = valid[qe[qi] + 1]
                b = best[qi]
                for dist in tables:
                    a = dist[su]
                    if a < 0:
                        continue
                    if v0:
                        x = dist[e0]
                        if x >= 0 and a + x < b:
                            b = a + x
                    if v1:
                        x = dist[e1]
                        if x >= 0 and a + x < b:
                            b = a + x
                best[qi] = b
                if l < r:
                    c1, c2 = qcols[qi]
                    if c1 <= mid and c2 <= mid:
                        left.append(qi)
                    elif c1 > mid and c2 > mid:
                        right.append(qi)
            if l < r:
                stack.append((l, mid, left))
                stack.append((mid + 1, r, right))
        for i in range(Q):
            out.append("YES" if best[i] <= qk[i] else "NO")
    print('\n'.join(out))
 
 
if __name__ == '__main__':
    main()
 