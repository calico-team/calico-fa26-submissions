import sys
from collections import defaultdict


def bfs(fb, fr, targets_b, targets_r, act_b, act_r, normal,
        n_col_first, n_col_last, m):
    """Bitset BFS on the (cell, mode) state graph.
    (fb, fr) are the starting frontiers in the blue / red planes.
    targets_b / targets_r are bitmasks of target cells per plane.
    Returns {cell: distance} for every target reached."""
    found = {}
    vis_b = fb
    vis_r = fr
    dist = 0
    # targets already occupied at distance 0
    hit = vis_b & targets_b
    while hit:
        low = hit & -hit
        found[low.bit_length() - 1] = 0
        hit ^= low
    hit = vis_r & targets_r
    while hit:
        low = hit & -hit
        found[low.bit_length() - 1] = 0
        hit ^= low
    remaining_b = targets_b
    remaining_r = targets_r
    for cell in found:
        remaining_b &= ~(1 << cell)
        remaining_r &= ~(1 << cell)
    while (fb or fr) and (remaining_b or remaining_r):
        dist += 1
        nb = ((fb << 1) & n_col_first) | ((fb >> 1) & n_col_last) | (fb << m) | (fb >> m)
        nb = (nb & act_b) | (fr & normal)
        nb &= ~vis_b
        nr = ((fr << 1) & n_col_first) | ((fr >> 1) & n_col_last) | (fr << m) | (fr >> m)
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


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    it = iter(data)
    t = int(next(it))
    out = []
    for _ in range(t):
        n = int(next(it)); m = int(next(it)); q = int(next(it))
        grid = [next(it).decode() for _ in range(n)]
        queries = []
        for _ in range(q):
            rs = int(next(it)); cs = int(next(it))
            re_ = int(next(it)); ce = int(next(it)); k = int(next(it))
            queries.append((rs, cs, re_, ce, k))

        act_b = 0
        act_r = 0
        normal = 0
        for r in range(n):
            row = grid[r]
            base = r * m
            for c, ch in enumerate(row):
                bit = 1 << (base + c)
                if ch == '.':
                    act_b |= bit
                    act_r |= bit
                    normal |= bit
                elif ch == 'B':
                    act_b |= bit
                else:  # 'R'
                    act_r |= bit
        col_first = 0
        col_last = 0
        for r in range(n):
            col_first |= 1 << (r * m)
            col_last |= 1 << (r * m + m - 1)

        ans = ["NO"] * q
        by_start = defaultdict(list)
        by_end = defaultdict(list)
        for idx, (rs, cs, re_, ce, k) in enumerate(queries):
            by_start[(rs, cs)].append(idx)
            by_end[(re_, ce)].append(idx)

        if len(by_start) <= len(by_end):
            # BFS from each start (blue mode) to its end cells (either mode)
            for (rs, cs), idxs in by_start.items():
                s = rs * m + cs
                targets = defaultdict(list)
                tmask = 0
                for idx in idxs:
                    e = queries[idx][2] * m + queries[idx][3]
                    targets[e].append(idx)
                    tmask |= 1 << e
                dist = bfs(1 << s, 0, tmask, tmask, act_b, act_r, normal,
                           ~col_first, ~col_last, m)
                for e, d in dist.items():
                    for idx in targets[e]:
                        if d <= queries[idx][4]:
                            ans[idx] = "YES"
        else:
            # BFS from each end cell (both modes) back to the start cells
            # (blue mode only) -- the state graph is undirected.
            for (re_, ce), idxs in by_end.items():
                e = re_ * m + ce
                targets = defaultdict(list)
                tmask = 0
                for idx in idxs:
                    s = queries[idx][0] * m + queries[idx][1]
                    targets[s].append(idx)
                    tmask |= 1 << s
                dist = bfs((1 << e) & act_b, (1 << e) & act_r, tmask, 0,
                           act_b, act_r, normal, ~col_first, ~col_last, m)
                for s, d in dist.items():
                    for idx in targets[s]:
                        if d <= queries[idx][4]:
                            ans[idx] = "YES"
        out.extend(ans)
    sys.stdout.write("\n".join(out))


if __name__ == "__main__":
    solve()
