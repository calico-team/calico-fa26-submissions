import sys
from collections import defaultdict

INF = 10 ** 18   # must stay above the maximum legal K (10**9)


# Flat BFS over the (cell, mode) state graph.
# State id = mode * nm + cell, mode 0 = blue, mode 1 = red.
# adj is a per-test-case cache: adj[u] stays None until some search
# first expands u, then it holds u's neighbour list, which later
# searches in the same test case reuse for free.
# sources: iterable of state ids.  If targets (a set of state ids) is
# given, the search stops once every target is reached or the depth
# exceeds cap.  Returns (dist, complete): dist holds -1 for unreached
# states; complete says the frontier ran out, i.e. dist is exact for
# the whole connected component of the sources.
def bfs(act, normal, nm, m, adj, sources, targets=None, cap=INF):
    act0, act1 = act
    dist = [-1] * (2 * nm)
    queue = []
    for s in sources:
        if dist[s] < 0:
            dist[s] = 0
            queue.append(s)
    need = len(targets) if targets else 0
    found = 0
    if targets:
        for s in sources:
            if s in targets:
                found += 1
    head = 0
    depth = 0
    complete = False
    while head < len(queue):
        if targets and (found >= need or depth >= cap):
            break
        level_end = len(queue)
        depth += 1
        while head < level_end:
            u = queue[head]
            head += 1
            nbrs = adj[u]
            if nbrs is None:
                if u < nm:
                    cell = u
                    a = act0
                    other = u + nm
                else:
                    cell = u - nm
                    a = act1
                    other = u - nm
                nbrs = []
                if normal[cell]:
                    nbrs.append(other)
                c = cell % m
                if c > 0 and a[cell - 1]:
                    nbrs.append(u - 1)
                if c + 1 < m and a[cell + 1]:
                    nbrs.append(u + 1)
                if cell >= m and a[cell - m]:
                    nbrs.append(u - m)
                if cell + m < nm and a[cell + m]:
                    nbrs.append(u + m)
                adj[u] = nbrs
            if targets:
                for v in nbrs:
                    if dist[v] < 0:
                        dist[v] = depth
                        queue.append(v)
                        if v in targets:
                            found += 1
            else:
                for v in nbrs:
                    if dist[v] < 0:
                        dist[v] = depth
                        queue.append(v)
    if head >= len(queue):
        complete = True
    return dist, complete


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    it = iter(data)
    t = int(next(it))
    out = []
    for _ in range(t):
        n = int(next(it)); m = int(next(it)); q = int(next(it))
        grid = [next(it) for _ in range(n)]
        queries = []
        for _ in range(q):
            rs = int(next(it)); cs = int(next(it))
            re_ = int(next(it)); ce = int(next(it)); k = int(next(it))
            queries.append((rs * m + cs, re_ * m + ce, k))
        nm = n * m

        # activity per mode + normal cells, as byte arrays
        act = [bytearray(nm), bytearray(nm)]
        normal = bytearray(nm)
        act0, act1 = act
        for r in range(n):
            row = grid[r]
            base = r * m
            for c in range(m):
                ch = row[c]
                cell = base + c
                if ch == 46:            # '.'
                    act0[cell] = 1
                    act1[cell] = 1
                    normal[cell] = 1
                elif ch == 66:          # 'B'
                    act0[cell] = 1
                else:                   # 'R'
                    act1[cell] = 1
        adj = [None] * (2 * nm)

        ans = [None] * q
        s_state = [0] * q
        e_blue = [-1] * q
        e_red = [-1] * q
        kval = [0] * q
        undecided = []
        for i, (sc, ec, k) in enumerate(queries):
            kval[i] = k
            s_state[i] = sc                    # starts are '.' -> blue
            if act0[ec]:
                e_blue[i] = ec
            if act1[ec]:
                e_red[i] = nm + ec
            if sc == ec:
                ans[i] = "YES"                 # distance 0 <= K
            else:
                undecided.append(i)

        # ---- landmark distance bounds ---------------------------------
        # For an exact distance field f and a query (s, e):
        #   |f(s) - f(e)| <= dist(s, e) <= f(s) + f(e)     (per end mode)
        # ub[i] = best upper bound so far, lbm?[i] = best lower bound
        # per end mode (bit 1 = blue end, bit 2 = red end in the masks),
        # dead[i] = end modes proven to sit in another component.
        ub = [INF] * q
        lbm0 = [0] * q
        lbm1 = [0] * q
        seen = [0] * q
        dead = [0] * q

        def apply_field(f):
            still = []
            for i in undecided:
                ds = f[s_state[i]]
                dd = dead[i]
                sn = seen[i]
                best_lb = INF
                eb = e_blue[i]
                if eb >= 0 and not dd & 1:
                    de = f[eb]
                    if ds >= 0 and de >= 0:
                        if ds + de < ub[i]:
                            ub[i] = ds + de
                        d = ds - de
                        if d < 0:
                            d = -d
                        if d > lbm0[i]:
                            lbm0[i] = d
                        sn |= 1
                    elif (ds >= 0) != (de >= 0):
                        dd |= 1
                    if sn & 1:
                        if lbm0[i] < best_lb:
                            best_lb = lbm0[i]
                    else:
                        best_lb = 0
                er = e_red[i]
                if er >= 0 and not dd & 2:
                    de = f[er]
                    if ds >= 0 and de >= 0:
                        if ds + de < ub[i]:
                            ub[i] = ds + de
                        d = ds - de
                        if d < 0:
                            d = -d
                        if d > lbm1[i]:
                            lbm1[i] = d
                        sn |= 2
                    elif (ds >= 0) != (de >= 0):
                        dd |= 2
                    if sn & 2:
                        if lbm1[i] < best_lb:
                            best_lb = lbm1[i]
                    else:
                        best_lb = 0
                dead[i] = dd
                seen[i] = sn
                live = (eb >= 0 and not dd & 1) or (er >= 0 and not dd & 2)
                if not live:
                    ans[i] = "NO"
                elif ub[i] <= kval[i]:
                    ans[i] = "YES"
                elif best_lb > kval[i]:
                    ans[i] = "NO"
                else:
                    still.append(i)
            undecided[:] = still

        if q > 8 and undecided:
            freq = defaultdict(int)
            for i in range(q):
                freq[s_state[i]] += 1
                if e_blue[i] >= 0:
                    freq[e_blue[i]] += 1
                if e_red[i] >= 0:
                    freq[e_red[i]] += 1
            cand = [s for s, _ in sorted(freq.items(),
                                         key=lambda kv: -kv[1])
                    [:300 if nm <= 2000 else 1500]]
            max_landmarks = 5 if nm <= 2000 else 8
            fields = []
            while undecided and len(fields) < max_landmarks:
                if len(fields) >= 2 and len(undecided) <= 6:
                    break            # residue BFS is cheaper from here
                if not fields:
                    root = cand[0]
                else:
                    root = -1
                    best_d = -1
                    for s in cand:
                        dmin = INF
                        for f in fields:
                            d = f[s]
                            if d < 0:
                                dmin = INF
                                break
                            if d < dmin:
                                dmin = d
                        if dmin > best_d:
                            best_d = dmin
                            root = s
                    if root < 0 or best_d <= 2:
                        break
                f, _ = bfs(act, normal, nm, m, adj, [root])
                fields.append(f)
                apply_field(f)

        # ---- residue: grouped BFS on the rarer side --------------------
        if undecided:
            by_start = defaultdict(list)
            by_end = defaultdict(list)
            for i in undecided:
                by_start[s_state[i]].append(i)
                by_end[queries[i][1]].append(i)
            use_start = len(by_start) <= len(by_end)
            groups = by_start if use_start else by_end
            order = sorted(groups.items(), key=lambda kv: -len(kv[1]))
            checks = 0
            for anchor, members in order:
                members = [i for i in members if ans[i] is None]
                if not members:
                    continue
                cap = max(kval[i] for i in members)
                if use_start:
                    sources = [anchor]
                    targets = set()
                    for i in members:
                        if e_blue[i] >= 0:
                            targets.add(e_blue[i])
                        if e_red[i] >= 0:
                            targets.add(e_red[i])
                else:
                    sources = []
                    if act0[anchor]:
                        sources.append(anchor)
                    if act1[anchor]:
                        sources.append(nm + anchor)
                    targets = set(s_state[i] for i in members)
                f, complete = bfs(act, normal, nm, m, adj, sources,
                                  targets, cap)
                if use_start:
                    for i in members:
                        d = INF
                        if e_blue[i] >= 0 and f[e_blue[i]] >= 0:
                            d = f[e_blue[i]]
                        if e_red[i] >= 0 and 0 <= f[e_red[i]] < d:
                            d = f[e_red[i]]
                        ans[i] = "YES" if d <= kval[i] else "NO"
                else:
                    for i in members:
                        d = f[s_state[i]]
                        ans[i] = "YES" if 0 <= d <= kval[i] else "NO"
                if complete:
                    # an exhausted search is an exact field: reuse it
                    # as a landmark for whatever is still open
                    undecided = [i for i in undecided if ans[i] is None]
                    if undecided:
                        checks += 1
                        if checks <= 10 or checks % 5 == 0:
                            apply_field(f)
        out.extend(a if a is not None else "NO" for a in ans)
    sys.stdout.write("\n".join(out))


if __name__ == "__main__":
    solve()
