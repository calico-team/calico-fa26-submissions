import sys
from itertools import chain, compress, repeat
from operator import add


def main():
    data = sys.stdin.buffer.read().split()
    t = int(data[0])
    pos = 1
    out = []
    INF = 1 << 60
    for _ in range(t):
        n = int(data[pos]); m = int(data[pos + 1]); q = int(data[pos + 2]); pos += 3
        rows = data[pos:pos + n]; pos += n
        S = 2 * n * m
        valid = [False] * S
        for c in range(m):
            for r in range(n):
                ch = rows[r][c]
                s = (c * n + r) * 2
                if ch == 46:
                    valid[s] = valid[s + 1] = True
                elif ch == 66:
                    valid[s] = True
                else:
                    valid[s + 1] = True
        adj = [()] * S
        for s in range(S):
            if not valid[s]:
                continue
            cell = s >> 1
            md = s & 1
            c, r = divmod(cell, n)
            nb = []
            if valid[s ^ 1]:
                nb.append(s ^ 1)
            if r > 0 and valid[s - 2]:
                nb.append(s - 2)
            if r < n - 1 and valid[s + 2]:
                nb.append(s + 2)
            if c > 0 and valid[s - 2 * n]:
                nb.append(s - 2 * n)
            if c < m - 1 and valid[s + 2 * n]:
                nb.append(s + 2 * n)
            adj[s] = tuple(nb)
        adjget = adj.__getitem__

        sc = [0] * q
        ec = [0] * q
        ss = [0] * q
        es = [0] * q
        kk = [0] * q
        for i in range(q):
            r1 = int(data[pos]); c1 = int(data[pos + 1]); r2 = int(data[pos + 2]); c2 = int(data[pos + 3]); kk[i] = int(data[pos + 4])
            pos += 5
            sc[i] = c1
            ec[i] = c2
            ss[i] = (c1 * n + r1) * 2
            es[i] = (c2 * n + r2) * 2
        ans = [INF] * q

        stack = [(0, m - 1, list(range(q)))]
        while stack:
            l, r, act = stack.pop()
            if not act:
                continue
            mid = (l + r) >> 1
            lo = 2 * n * l
            rng = set(compress(range(lo, 2 * n * (r + 1)), valid[lo:2 * n * (r + 1)]))
            groups = {}
            for i in act:
                s0 = ss[i]
                if s0 in groups:
                    groups[s0].append(i)
                else:
                    groups[s0] = [i]
            nsrc = sum(valid[2 * n * mid:2 * n * (mid + 1)])
            if len(groups) <= nsrc * (r - l + 1).bit_length():
                for src, qs in groups.items():
                    tg = {}
                    for i in qs:
                        e = es[i]
                        tg[e] = INF
                        tg[e + 1] = INF
                    need = {x for x in tg if x in rng}
                    if src in need:
                        tg[src] = 0
                        need.discard(src)
                    unvis = rng.copy()
                    unvis.discard(src)
                    frontier = (src,)
                    d = 0
                    while frontier and need:
                        d += 1
                        frontier = unvis.intersection(chain.from_iterable(map(adjget, frontier)))
                        unvis -= frontier
                        h = frontier & need
                        if h:
                            tg.update(zip(h, repeat(d)))
                            need -= h
                    for i in qs:
                        e = es[i]
                        v = tg[e]
                        if tg[e + 1] < v:
                            v = tg[e + 1]
                        if v < ans[i]:
                            ans[i] = v
                continue
            sidx = [ss[i] for i in act]
            e0 = [es[i] for i in act]
            e1 = [x + 1 for x in e0]
            ends = set(sidx)
            ends.update(e0)
            ends.update(e1)
            best = [INF] * len(act)
            base = 2 * n * mid
            for src in range(base, base + 2 * n):
                if not valid[src]:
                    continue
                unvis = rng.copy()
                unvis.discard(src)
                dd = {src: 0}
                frontier = (src,)
                d = 0
                while frontier:
                    d += 1
                    frontier = unvis.intersection(chain.from_iterable(map(adjget, frontier)))
                    unvis -= frontier
                    h = frontier & ends
                    if h:
                        dd.update(zip(h, repeat(d)))
                g = dd.get
                best = list(map(min, best, map(add, map(g, sidx, repeat(INF)),
                                               map(min, map(g, e0, repeat(INF)), map(g, e1, repeat(INF))))))
            left = []
            right = []
            for j, i in enumerate(act):
                if best[j] < ans[i]:
                    ans[i] = best[j]
                a = sc[i]; b = ec[i]
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
