import sys
import time
from collections import defaultdict

INF = float("inf")


# ---------------------------------------------------------------------------
# Bitset BFS on the (cell, mode) state graph -- same expansion as the first
# version, but it stops as soon as every target is found or the depth passes
# max_depth (no query in the group can still become a YES beyond that).
# (fb, fr) are the starting frontiers in the blue / red planes,
# targets_b / targets_r are bitmasks of target cells per plane.
# Returns {cell: distance} for every target reached in either plane.
# ---------------------------------------------------------------------------
def bitset_bfs(fb, fr, targets_b, targets_r, act_b, act_r, normal,
               not_first, not_last, m, max_depth):
    found = {}
    vis_b = fb
    vis_r = fr
    remaining_b = targets_b
    remaining_r = targets_r
    hit = vis_b & remaining_b
    while hit:
        low = hit & -hit
        cell = low.bit_length() - 1
        found[cell] = 0
        remaining_b &= ~low
        remaining_r &= ~low
        hit ^= low
    hit = vis_r & remaining_r
    while hit:
        low = hit & -hit
        cell = low.bit_length() - 1
        found[cell] = 0
        remaining_b &= ~low
        remaining_r &= ~low
        hit ^= low
    dist = 0
    while (fb or fr) and (remaining_b or remaining_r) and dist < max_depth:
        dist += 1
        nb = ((fb << 1) & not_first) | ((fb >> 1) & not_last) | (fb << m) | (fb >> m)
        nb = (nb & act_b) | (fr & normal)
        nb &= ~vis_b
        nr = ((fr << 1) & not_first) | ((fr >> 1) & not_last) | (fr << m) | (fr >> m)
        nr = (nr & act_r) | (fb & normal)
        nr &= ~vis_r
        vis_b |= nb
        vis_r |= nr
        fb, fr = nb, nr
        hit = vis_b & remaining_b
        while hit:
            low = hit & -hit
            cell = low.bit_length() - 1
            found[cell] = dist
            remaining_b &= ~low
            remaining_r &= ~low
            hit ^= low
        hit = vis_r & remaining_r
        while hit:
            low = hit & -hit
            cell = low.bit_length() - 1
            found[cell] = dist
            remaining_b &= ~low
            remaining_r &= ~low
            hit ^= low
    return found


# ---------------------------------------------------------------------------
# Bidirectional BFS between one start state and a set of end states on the
# explicit state graph (state = mode * NM + cell).  Used for sources with
# only a couple of queries: in maze-like grids the two search balls stay
# thin, so this beats a full bitset sweep.  Returns the exact distance,
# INF when unreachable, or None when the expansion cap was hit (caller
# falls back to the bitset BFS in that case).
# ---------------------------------------------------------------------------
def bidir_bfs(act, normal, nm, n, m, start, ends, cap):
    end_set = set(ends)
    if start in end_set:
        return 0
    dist_f = {start: 0}
    dist_b = {}
    for e in ends:
        dist_b[e] = 0
    front_f = [start]
    front_b = list(ends)
    depth_f = 0
    depth_b = 0
    best = INF
    expanded = 0
    act0, act1 = act[0], act[1]
    nm_minus = nm

    while front_f and front_b:
        if depth_f + depth_b >= best:
            break
        if len(front_f) <= len(front_b):
            depth_f += 1
            new_front = []
            for u in front_f:
                mode, cell = divmod(u, nm_minus)
                a = act1 if mode else act0
                c = cell % m
                if c > 0 and a[cell - 1]:
                    v = u - 1
                    expanded += 1
                    dv = dist_b.get(v)
                    if dv is not None and depth_f + dv < best:
                        best = depth_f + dv
                    if v not in dist_f:
                        dist_f[v] = depth_f
                        new_front.append(v)
                if c + 1 < m and a[cell + 1]:
                    v = u + 1
                    expanded += 1
                    dv = dist_b.get(v)
                    if dv is not None and depth_f + dv < best:
                        best = depth_f + dv
                    if v not in dist_f:
                        dist_f[v] = depth_f
                        new_front.append(v)
                if cell >= m and a[cell - m]:
                    v = u - m
                    expanded += 1
                    dv = dist_b.get(v)
                    if dv is not None and depth_f + dv < best:
                        best = depth_f + dv
                    if v not in dist_f:
                        dist_f[v] = depth_f
                        new_front.append(v)
                if cell + m < nm_minus and a[cell + m]:
                    v = u + m
                    expanded += 1
                    dv = dist_b.get(v)
                    if dv is not None and depth_f + dv < best:
                        best = depth_f + dv
                    if v not in dist_f:
                        dist_f[v] = depth_f
                        new_front.append(v)
                if normal[cell]:
                    v = u + nm if mode == 0 else u - nm
                    expanded += 1
                    dv = dist_b.get(v)
                    if dv is not None and depth_f + dv < best:
                        best = depth_f + dv
                    if v not in dist_f:
                        dist_f[v] = depth_f
                        new_front.append(v)
            front_f = new_front
        else:
            depth_b += 1
            new_front = []
            for u in front_b:
                mode, cell = divmod(u, nm_minus)
                a = act1 if mode else act0
                c = cell % m
                if c > 0 and a[cell - 1]:
                    v = u - 1
                    expanded += 1
                    dv = dist_f.get(v)
                    if dv is not None and depth_b + dv < best:
                        best = depth_b + dv
                    if v not in dist_b:
                        dist_b[v] = depth_b
                        new_front.append(v)
                if c + 1 < m and a[cell + 1]:
                    v = u + 1
                    expanded += 1
                    dv = dist_f.get(v)
                    if dv is not None and depth_b + dv < best:
                        best = depth_b + dv
                    if v not in dist_b:
                        dist_b[v] = depth_b
                        new_front.append(v)
                if cell >= m and a[cell - m]:
                    v = u - m
                    expanded += 1
                    dv = dist_f.get(v)
                    if dv is not None and depth_b + dv < best:
                        best = depth_b + dv
                    if v not in dist_b:
                        dist_b[v] = depth_b
                        new_front.append(v)
                if cell + m < nm_minus and a[cell + m]:
                    v = u + m
                    expanded += 1
                    dv = dist_f.get(v)
                    if dv is not None and depth_b + dv < best:
                        best = depth_b + dv
                    if v not in dist_b:
                        dist_b[v] = depth_b
                        new_front.append(v)
                if normal[cell]:
                    v = u + nm if mode == 0 else u - nm
                    expanded += 1
                    dv = dist_f.get(v)
                    if dv is not None and depth_b + dv < best:
                        best = depth_b + dv
                    if v not in dist_b:
                        dist_b[v] = depth_b
                        new_front.append(v)
            front_b = new_front
        if expanded > cap:
            return None
    return best


class DSU:
    def __init__(self, size):
        self.parent = list(range(size))

    def find(self, x):
        parent = self.parent
        root = x
        while parent[root] != root:
            root = parent[root]
        while parent[x] != root:
            parent[x], x = root, parent[x]
        return root

    def union(self, a, b):
        ra, rb = self.find(a), self.find(b)
        if ra != rb:
            self.parent[ra] = rb


# ---------------------------------------------------------------------------
# Plain array/dict BFS from a set of source states until every target state
# is found or max_depth is exceeded.  For small components this is far
# cheaper than a bitset sweep over the whole grid.  Returns {state: dist}.
# ---------------------------------------------------------------------------
def sparse_bfs(act, normal, nm, n, m, sources, targets, max_depth):
    dist = {}
    front = []
    for s in sources:
        if s not in dist:
            dist[s] = 0
            front.append(s)
    found = {}
    for s in sources:
        if s in targets:
            found[s] = 0
    act0, act1 = act[0], act[1]
    depth = 0
    remaining = len(targets) - len(found)
    while front and remaining > 0 and depth < max_depth:
        depth += 1
        new_front = []
        for u in front:
            mode, cell = divmod(u, nm)
            a = act1 if mode else act0
            c = cell % m
            if c > 0 and a[cell - 1]:
                v = u - 1
                if v not in dist:
                    dist[v] = depth
                    new_front.append(v)
                    if v in targets:
                        found[v] = depth
                        remaining -= 1
            if c + 1 < m and a[cell + 1]:
                v = u + 1
                if v not in dist:
                    dist[v] = depth
                    new_front.append(v)
                    if v in targets:
                        found[v] = depth
                        remaining -= 1
            if cell >= m and a[cell - m]:
                v = u - m
                if v not in dist:
                    dist[v] = depth
                    new_front.append(v)
                    if v in targets:
                        found[v] = depth
                        remaining -= 1
            if cell + m < nm and a[cell + m]:
                v = u + m
                if v not in dist:
                    dist[v] = depth
                    new_front.append(v)
                    if v in targets:
                        found[v] = depth
                        remaining -= 1
            if normal[cell]:
                v = u + nm if mode == 0 else u - nm
                if v not in dist:
                    dist[v] = depth
                    new_front.append(v)
                    if v in targets:
                        found[v] = depth
                        remaining -= 1
        front = new_front
    return found


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    it = iter(data)
    t = int(next(it))
    out = []
    for _ in range(t):
        n = int(next(it)); m = int(next(it)); q = int(next(it))
        grid = [next(it) for _ in range(n)]          # rows as bytes
        queries = []
        for _ in range(q):
            rs = int(next(it)); cs = int(next(it))
            re_ = int(next(it)); ce = int(next(it)); k = int(next(it))
            queries.append((rs, cs, re_, ce, k))
        nm = n * m

        # activity bitmasks per plane (bit = cell), plus normal-cell mask
        act_b = 0
        act_r = 0
        normal = 0
        # activity byte arrays for the explicit-state BFS / DSU
        act = [bytearray(nm), bytearray(nm)]
        normal_ba = bytearray(nm)
        for r in range(n):
            row = grid[r]
            base = r * m
            for c in range(m):
                ch = row[c]
                cell = base + c
                bit = 1 << cell
                if ch == 46:        # '.'
                    act_b |= bit
                    act_r |= bit
                    normal |= bit
                    act[0][cell] = 1
                    act[1][cell] = 1
                    normal_ba[cell] = 1
                elif ch == 66:      # 'B'
                    act_b |= bit
                    act[0][cell] = 1
                else:               # 'R'
                    act_r |= bit
                    act[1][cell] = 1
        col_first = 0
        col_last = 0
        for r in range(n):
            col_first |= 1 << (r * m)
            col_last |= 1 << (r * m + m - 1)
        not_first = ~col_first
        not_last = ~col_last

        ans = ["NO"] * q

        # --- components: instant NO for unreachable pairs, and a filter ---
        # --- so BFS target sets only contain reachable targets.        ---
        pending = list(range(q))
        dsu = None
        if q >= 200:
            dsu = DSU(2 * nm)
            for cell in range(nm):
                r, c = divmod(cell, m)
                for mode in (0, 1):
                    if not act[mode][cell]:
                        continue
                    st = mode * nm + cell
                    if c + 1 < m and act[mode][cell + 1]:
                        dsu.union(st, st + 1)
                    if r + 1 < n and act[mode][cell + m]:
                        dsu.union(st, st + m)
                    if normal_ba[cell]:
                        dsu.union(cell, nm + cell)
            still = []
            for qi in pending:
                rs, cs, re_, ce, k = queries[qi]
                s_comp = dsu.find(rs * m + cs)            # start state: blue
                e_cell = re_ * m + ce
                ok = False
                if act[0][e_cell] and dsu.find(e_cell) == s_comp:
                    ok = True
                if act[1][e_cell] and dsu.find(nm + e_cell) == s_comp:
                    ok = True
                if ok:
                    still.append(qi)
            pending = still

        # --- group the remaining queries by start cell and by end cell ---
        by_start = defaultdict(list)
        by_end = defaultdict(list)
        for qi in pending:
            rs, cs, re_, ce, k = queries[qi]
            by_start[rs * m + cs].append(qi)
            by_end[re_ * m + ce].append(qi)
        use_start = len(by_start) <= len(by_end)
        groups = by_start if use_start else by_end

        # --- small groups: bidirectional BFS per query, but only when ---
        # --- the grid is big enough that a grouped sweep is pricey;   ---
        # --- on small grids the grouped engines below are cheaper.    ---
        todo_groups = defaultdict(list)
        for src, qlist in groups.items():
            if len(qlist) <= 3 and nm >= 8000:
                for qi in qlist:
                    rs, cs, re_, ce, k = queries[qi]
                    s_state = rs * m + cs               # blue mode
                    e_cell = re_ * m + ce
                    ends = []
                    if act[0][e_cell]:
                        ends.append(e_cell)
                    if act[1][e_cell]:
                        ends.append(nm + e_cell)
                    d = bidir_bfs(act, normal_ba, nm, n, m, s_state, ends,
                                  cap=12000)
                    if d is None:
                        todo_groups[src].append(qi)
                    elif d <= k:
                        ans[qi] = "YES"
            else:
                todo_groups[src] = qlist

        # --- remaining groups: one grouped BFS per source.  Two engines ---
        # --- are available (sparse dict BFS / bitset sweep); which one  ---
        # --- is faster depends on the grid's shape, so on big grids     ---
        # --- they are raced on the largest group and the winner is      ---
        # --- used for the rest of this test case.                       ---
        def resolve_sparse(src, qlist):
            max_k = max(queries[qi][4] for qi in qlist)
            if use_start:
                tset = set()
                for qi in qlist:
                    e_cell = queries[qi][2] * m + queries[qi][3]
                    if act[0][e_cell]:
                        tset.add(e_cell)
                    if act[1][e_cell]:
                        tset.add(nm + e_cell)
                found = sparse_bfs(act, normal_ba, nm, n, m, [src], tset,
                                   max_k)
                best = {}
                for st, d in found.items():
                    cell = st % nm
                    if cell not in best or d < best[cell]:
                        best[cell] = d
                for qi in qlist:
                    e_cell = queries[qi][2] * m + queries[qi][3]
                    d = best.get(e_cell)
                    if d is not None and d <= queries[qi][4]:
                        ans[qi] = "YES"
            else:
                targets = {}
                tset = set()
                for qi in qlist:
                    s_cell = queries[qi][0] * m + queries[qi][1]
                    tset.add(s_cell)
                    targets.setdefault(s_cell, []).append(qi)
                sources = []
                if act[0][src]:
                    sources.append(src)
                if act[1][src]:
                    sources.append(nm + src)
                found = sparse_bfs(act, normal_ba, nm, n, m, sources, tset,
                                   max_k)
                for s_cell, idxs in targets.items():
                    d = found.get(s_cell)
                    if d is not None:
                        for qi in idxs:
                            if d <= queries[qi][4]:
                                ans[qi] = "YES"

        def resolve_bitset(src, qlist):
            max_k = max(queries[qi][4] for qi in qlist)
            if use_start:
                targets = {}
                tmask = 0
                for qi in qlist:
                    e_cell = queries[qi][2] * m + queries[qi][3]
                    targets.setdefault(e_cell, []).append(qi)
                    tmask |= 1 << e_cell
                found = bitset_bfs(1 << src, 0, tmask, tmask, act_b, act_r,
                                   normal, not_first, not_last, m, max_k)
                for e_cell, idxs in targets.items():
                    d = found.get(e_cell)
                    if d is not None:
                        for qi in idxs:
                            if d <= queries[qi][4]:
                                ans[qi] = "YES"
            else:
                targets = {}
                tmask = 0
                for qi in qlist:
                    s_cell = queries[qi][0] * m + queries[qi][1]
                    targets.setdefault(s_cell, []).append(qi)
                    tmask |= 1 << s_cell
                fb = (1 << src) & act_b
                fr = (1 << src) & act_r
                found = bitset_bfs(fb, fr, tmask, 0, act_b, act_r,
                                   normal, not_first, not_last, m, max_k)
                for s_cell, idxs in targets.items():
                    d = found.get(s_cell)
                    if d is not None:
                        for qi in idxs:
                            if d <= queries[qi][4]:
                                ans[qi] = "YES"

        todo_items = list(todo_groups.items())
        if todo_items:
            if nm <= 2000:
                engine = resolve_bitset
                skip = None
            else:
                big_src, big_list = max(todo_items,
                                        key=lambda kv: len(kv[1]))
                t0 = time.perf_counter()
                resolve_sparse(big_src, big_list)
                t_sparse = time.perf_counter() - t0
                t0 = time.perf_counter()
                resolve_bitset(big_src, big_list)
                t_bitset = time.perf_counter() - t0
                engine = resolve_sparse if t_sparse <= t_bitset \
                    else resolve_bitset
                skip = big_src
            for src, qlist in todo_items:
                if src != skip:
                    engine(src, qlist)
        out.extend(ans)
    sys.stdout.write("\n".join(out))


if __name__ == "__main__":
    solve()
