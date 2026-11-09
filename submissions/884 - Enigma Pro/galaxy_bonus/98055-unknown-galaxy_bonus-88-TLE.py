import sys


def main():
    lines = [x.split() for x in sys.stdin.buffer.read().splitlines()]
    lines = [x for x in lines if x]
    t = int(lines[0][0])
    pos = 1
    out = []
    INF = 1 << 60
    for _ in range(t):
        hd = lines[pos]; pos += 1
        n = int(hd[0]); m = int(hd[1]); q = int(hd[2])
        rows = [b''.join(x) for x in lines[pos:pos + n]]; pos += n
        h = n + 1
        cs = 2 * h
        S = cs * m
        valid = [0] * S
        for c in range(m):
            base = c * cs
            for r in range(n):
                ch = rows[r][c]
                s = base + 2 * r
                if ch == 46:
                    valid[s] = 1
                    valid[s + 1] = 1
                elif ch == 66:
                    valid[s] = 1
                else:
                    valid[s + 1] = 1

        nb5 = [S] * (5 * S)
        for s in range(S):
            if valid[s]:
                b = 5 * s
                v = s ^ 1
                if valid[v]:
                    nb5[b] = v
                v = s - 2
                if v >= 0 and valid[v]:
                    nb5[b + 1] = v
                v = s + 2
                if v < S and valid[v]:
                    nb5[b + 2] = v
                v = s - cs
                if v >= 0 and valid[v]:
                    nb5[b + 3] = v
                v = s + cs
                if v < S and valid[v]:
                    nb5[b + 4] = v

        sc = [0] * q
        ec = [0] * q
        ss = [0] * q
        es = [0] * q
        kk = [0] * q
        for i in range(q):
            w = lines[pos]; pos += 1
            r1 = int(w[0]); c1 = int(w[1]); r2 = int(w[2]); c2 = int(w[3])
            kk[i] = int(w[4]) if len(w) > 4 else INF - 1
            sc[i] = c1
            ec[i] = c2
            ss[i] = c1 * cs + 2 * r1
            es[i] = c2 * cs + 2 * r2
        ans = [INF] * q

        dist = [0] * (S + 1)
        seen = [0] * (S + 1)
        tmark = [0] * S
        queue = [0] * S
        stamp = 0

        stack = [(0, m - 1, list(range(q)))]
        while stack:
            l, r, act = stack.pop()
            if not act:
                continue
            mid = (l + r) >> 1
            lo = l * cs
            hi = (r + 1) * cs
            groups = {}
            for i in act:
                s0 = ss[i]
                g = groups.get(s0)
                if g is None:
                    groups[s0] = [i]
                else:
                    g.append(i)
            base = mid * cs
            nsrc = 0
            for s in range(base, base + cs):
                nsrc += valid[s]
            direct = len(groups) <= nsrc * (r - l + 1).bit_length()
            if direct:
                srcs = list(groups.keys())
            else:
                srcs = [s for s in range(base, base + cs) if valid[s]]
                best = [INF] * len(act)
            for src in srcs:
                stamp += 1
                seen[S] = stamp
                seen[src] = stamp
                dist[src] = 0
                queue[0] = src
                qh = 0
                qt = 1
                need = -1
                if direct:
                    need = 0
                    for i in groups[src]:
                        e = es[i]
                        if lo <= e < hi:
                            if valid[e] and tmark[e] != stamp:
                                tmark[e] = stamp
                                need += 1
                            if valid[e + 1] and tmark[e + 1] != stamp:
                                tmark[e + 1] = stamp
                                need += 1
                    if tmark[src] == stamp:
                        need -= 1
                if l > 0:
                    for v in range(lo - cs, lo):
                        seen[v] = stamp
                if r < m - 1:
                    for v in range(hi, hi + cs):
                        seen[v] = stamp
                while qh < qt and need != 0:
                    u = queue[qh]
                    qh += 1
                    if tmark[u] == stamp and u != src:
                        need -= 1
                        if need == 0:
                            break
                    b5 = u * 5
                    du = dist[u] + 1
                    v = nb5[b5]
                    if seen[v] != stamp:
                        seen[v] = stamp
                        dist[v] = du
                        queue[qt] = v
                        qt += 1
                    v = nb5[b5 + 1]
                    if seen[v] != stamp:
                        seen[v] = stamp
                        dist[v] = du
                        queue[qt] = v
                        qt += 1
                    v = nb5[b5 + 2]
                    if seen[v] != stamp:
                        seen[v] = stamp
                        dist[v] = du
                        queue[qt] = v
                        qt += 1
                    v = nb5[b5 + 3]
                    if seen[v] != stamp:
                        seen[v] = stamp
                        dist[v] = du
                        queue[qt] = v
                        qt += 1
                    v = nb5[b5 + 4]
                    if seen[v] != stamp:
                        seen[v] = stamp
                        dist[v] = du
                        queue[qt] = v
                        qt += 1
                if direct:
                    for i in groups[src]:
                        e = es[i]
                        v = INF
                        if lo <= e < hi:
                            if seen[e] == stamp:
                                v = dist[e]
                            if seen[e + 1] == stamp and dist[e + 1] < v:
                                v = dist[e + 1]
                        if v < ans[i]:
                            ans[i] = v
                else:
                    j = 0
                    for i in act:
                        a = ss[i]
                        if seen[a] == stamp:
                            e = es[i]
                            v = INF
                            if seen[e] == stamp:
                                v = dist[e]
                            if seen[e + 1] == stamp and dist[e + 1] < v:
                                v = dist[e + 1]
                            v += dist[a]
                            if v < best[j]:
                                best[j] = v
                        j += 1
            if direct:
                continue
            left = []
            right = []
            j = 0
            for i in act:
                if best[j] < ans[i]:
                    ans[i] = best[j]
                j += 1
                a = sc[i]
                b = ec[i]
                if a < mid and b < mid:
                    left.append(i)
                elif a > mid and b > mid:
                    right.append(i)
            if l < mid:
                stack.append((l, mid - 1, left))
            if mid < r:
                stack.append((mid + 1, r, right))

        for i in range(q):
            out.append("YES" if ans[i] <= kk[i] else "NO")
    sys.stdout.write("\n".join(out) + "\n")


main()
