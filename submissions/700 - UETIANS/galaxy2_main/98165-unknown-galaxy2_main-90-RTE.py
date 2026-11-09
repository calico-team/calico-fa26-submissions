import sys
from operator import add


def main():
    data = sys.stdin.buffer.read().split()
    pos = 0
    t = int(data[pos])
    pos += 1
    out = []
    INF = 1 << 30

    for _ in range(t):
        n = int(data[pos])
        m = int(data[pos + 1])
        qn = int(data[pos + 2])
        pos += 3
        grid = [data[pos + i].decode() for i in range(n)]
        pos += n
        qvals = list(map(int, data[pos:pos + 5 * qn]))
        pos += 5 * qn

        # ---------------------------------------------------------------
        # State graph: state id = col * W2 + row * 2 + mode (0 blue, 1 red)
        # Edges: walk to an adjacent tile that is active in the same mode,
        # or spin (flip mode) while standing on a normal tile. All cost 1.
        # ---------------------------------------------------------------
        W2 = 2 * n
        total = m * W2
        actm = (
            [[ch != 'R' for ch in row] for row in grid],  # blue mode
            [[ch != 'B' for ch in row] for row in grid],  # red mode
        )
        adj = [[] for _ in range(total)]
        isact = [False] * total
        colcnt = [0] * m
        for mode in (0, 1):
            act = actm[mode]
            for r in range(n):
                arow = act[r]
                for c in range(m):
                    if not arow[c]:
                        continue
                    v = c * W2 + 2 * r + mode
                    isact[v] = True
                    colcnt[c] += 1
                    nb = adj[v]
                    if r > 0 and act[r - 1][c]:
                        nb.append(v - 2)
                    if r < n - 1 and act[r + 1][c]:
                        nb.append(v + 2)
                    if c > 0 and arow[c - 1]:
                        nb.append(v - W2)
                    if c < m - 1 and arow[c + 1]:
                        nb.append(v + W2)
                    if grid[r][c] == '.':
                        nb.append(v ^ 1)

        # connected components of the state graph (used for quick answers)
        comp = [-1] * total
        csize = []
        for s in range(total):
            if isact[s] and comp[s] < 0:
                cid = len(csize)
                comp[s] = cid
                stack = [s]
                cnt = 0
                while stack:
                    v = stack.pop()
                    cnt += 1
                    for u in adj[v]:
                        if comp[u] < 0:
                            comp[u] = cid
                            stack.append(u)
                csize.append(cnt)

        # ---------------------------------------------------------------
        # Queries
        # ---------------------------------------------------------------
        ans = [False] * qn
        qa = [0] * qn     # start column
        qb = [0] * qn     # end column
        ida = [0] * qn    # start state (blue mode)
        eb = [-1] * qn    # end state in blue mode (or -1)
        er = [-1] * qn    # end state in red mode (or -1)
        qk = [0] * qn
        vlb = [0] * qn    # lower bound on non-horizontal cost
        pending = []
        for q in range(qn):
            ra, ca, rb, cb, K = qvals[5 * q:5 * q + 5]
            if ra == rb and ca == cb:
                ans[q] = True
                continue
            chb = grid[rb][cb]
            v = abs(ra - rb) + (1 if chb == 'R' else 0)
            if v + abs(ca - cb) > K:
                continue
            a = ca * W2 + 2 * ra
            if chb != 'R':
                e1 = cb * W2 + 2 * rb
                e2 = e1 + 1 if chb == '.' else -1
                tc = comp[e1]
            else:
                e1 = -1
                e2 = cb * W2 + 2 * rb + 1
                tc = comp[e2]
            cid = comp[a]
            if cid != tc:
                continue
            if K >= csize[cid] - 1:
                ans[q] = True
                continue
            qa[q] = ca
            qb[q] = cb
            ida[q] = a
            eb[q] = e1
            er[q] = e2
            qk[q] = K
            vlb[q] = v
            pending.append(q)

        if pending:
            dists = [[INF] * total for _ in range(W2)]
            dd = [INF] * total

            def solve_node(l, r, qs):
                """qs: unresolved queries with both endpoints inside [l, r]."""
                if not qs:
                    return
                lo = l * W2
                hi = (r + 1) * W2
                mid = (l + r) >> 1
                nsrc = colcnt[mid]

                # ---- few queries: run a direct BFS per query inside [l, r]
                if len(qs) < 2 * nsrc + 2:
                    saved = trim(lo, hi)
                    blk = [INF] * (hi - lo)
                    for q in qs:
                        K = qk[q]
                        dd[lo:hi] = blk
                        s = ida[q]
                        t1 = eb[q]
                        t2 = er[q]
                        dd[s] = 0
                        frontier = [s]
                        d = 0
                        found = False
                        while frontier and d < K and not found:
                            d += 1
                            nxt = []
                            app = nxt.append
                            for v in frontier:
                                for u in adj[v]:
                                    if dd[u] > d:
                                        dd[u] = d
                                        app(u)
                            frontier = nxt
                            if t1 >= 0 and dd[t1] <= d:
                                found = True
                            elif t2 >= 0 and dd[t2] <= d:
                                found = True
                        if found:
                            ans[q] = True
                    restore(saved)
                    return

                # ---- split the queries around the separator column `mid`
                left = []
                right = []
                here = []
                for q in qs:
                    x = qa[q]
                    y = qb[q]
                    if x < mid and y < mid:
                        left.append(q)
                    elif x > mid and y > mid:
                        right.append(q)
                    else:
                        here.append(q)
                if left:
                    solve_node(l, mid - 1, left)
                if right:
                    solve_node(mid + 1, r, right)

                # ---- queries that need this separator
                need = here
                for q in left:
                    if not ans[q]:
                        x = qa[q]
                        y = qb[q]
                        if (mid - x) + (mid - y) + vlb[q] <= qk[q]:
                            need.append(q)
                for q in right:
                    if not ans[q]:
                        x = qa[q]
                        y = qb[q]
                        if (x - mid) + (y - mid) + vlb[q] <= qk[q]:
                            need.append(q)
                if not need:
                    return

                cap = 0
                for q in need:
                    if qk[q] > cap:
                        cap = qk[q]

                saved = trim(lo, hi)
                blk = [INF] * (hi - lo)
                srcs = [v for v in range(mid * W2, mid * W2 + W2) if isact[v]]
                for k, s in enumerate(srcs):
                    dk = dists[k]
                    dk[lo:hi] = blk
                    dk[s] = 0
                    frontier = [s]
                    d = 0
                    while frontier and d < cap:
                        d += 1
                        nxt = []
                        app = nxt.append
                        for v in frontier:
                            for u in adj[v]:
                                if dk[u] > d:
                                    dk[u] = d
                                    app(u)
                        frontier = nxt
                restore(saved)

                ns = len(srcs)
                T = list(zip(*[dists[k][lo:hi] for k in range(ns)]))
                for q in need:
                    ta = T[ida[q] - lo]
                    e1 = eb[q]
                    best = min(map(add, ta, T[e1 - lo])) if e1 >= 0 else INF
                    e2 = er[q]
                    if e2 >= 0:
                        c2 = min(map(add, ta, T[e2 - lo]))
                        if c2 < best:
                            best = c2
                    if best <= qk[q]:
                        ans[q] = True

            def trim(lo, hi):
                """Cut edges leaving [lo, hi); returns data to undo it."""
                saved = []
                for v in range(lo, lo + W2):
                    a = adj[v]
                    if a:
                        na = [u for u in a if u >= lo]
                        if len(na) != len(a):
                            saved.append((v, a))
                            adj[v] = na
                for v in range(hi - W2, hi):
                    a = adj[v]
                    if a:
                        na = [u for u in a if u < hi]
                        if len(na) != len(a):
                            saved.append((v, a))
                            adj[v] = na
                return saved

            def restore(saved):
                for v, a in reversed(saved):
                    adj[v] = a

            solve_node(0, m - 1, pending)

        out.append("\n".join("YES" if x else "NO" for x in ans))

    sys.stdout.write("\n".join(out) + "\n")


main()
