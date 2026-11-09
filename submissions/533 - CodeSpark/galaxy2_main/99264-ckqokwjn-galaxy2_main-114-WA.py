import sys

INF = 10 ** 9


def solve_case(n, m, grid, queries):
    S = 2 * n
    total = m * S
    active = [False] * total
    nbrs = [None] * total
    for c in range(m):
        for r in range(n):
            ch = grid[r][c]
            for mode in range(2):
                ok = ch == '.' or (ch == 'B' and mode == 0) or (ch == 'R' and mode == 1)
                active[(c * n + r) * 2 + mode] = ok
    for c in range(m):
        for r in range(n):
            for mode in range(2):
                sid = (c * n + r) * 2 + mode
                if not active[sid]:
                    nbrs[sid] = []
                    continue
                lst = []
                if r > 0 and active[sid - 2]:
                    lst.append(sid - 2)
                if r + 1 < n and active[sid + 2]:
                    lst.append(sid + 2)
                if c > 0 and active[sid - S]:
                    lst.append(sid - S)
                if c + 1 < m and active[sid + S]:
                    lst.append(sid + S)
                if grid[r][c] == '.':
                    lst.append(sid ^ 1)
                nbrs[sid] = lst

    q = len(queries)
    best = [INF] * q
    start_state = [0] * q
    end_states = [None] * q
    scol = [0] * q
    ecol = [0] * q
    for i, (r0, c0, r1, c1, k) in enumerate(queries):
        start_state[i] = (c0 * n + r0) * 2
        e0 = (c1 * n + r1) * 2
        end_states[i] = (e0, e0 + 1)
        scol[i] = c0
        ecol[i] = c1

    def work(lo, hi, ids):
        if not ids:
            return
        mid = (lo + hi) // 2
        base = lo * S
        width = (hi - lo + 1) * S
        sources = [s for s in range(mid * S, mid * S + S) if active[s]]
        tables = []
        for src in sources:
            dist = [INF] * width
            dist[src - base] = 0
            frontier = [src]
            d = 0
            while frontier:
                d += 1
                nxt = []
                for u in frontier:
                    for v in nbrs[u]:
                        if lo * S <= v < (hi + 1) * S and dist[v - base] == INF:
                            dist[v - base] = d
                            nxt.append(v)
                frontier = nxt
            tables.append(dist)
        left = []
        right = []
        for i in ids:
            a = start_state[i] - base
            e0, e1 = end_states[i]
            e0 -= base
            e1 -= base
            cur = best[i]
            for dist in tables:
                da = dist[a]
                if da >= cur:
                    continue
                db = dist[e0]
                d1 = dist[e1]
                if d1 < db:
                    db = d1
                if da + db < cur:
                    cur = da + db
            best[i] = cur
            if scol[i] < mid and ecol[i] < mid:
                left.append(i)
            elif scol[i] > mid and ecol[i] > mid:
                right.append(i)
        if lo < mid:
            work(lo, mid - 1, left)
        if mid < hi:
            work(mid + 1, hi, right)

    ids = []
    for i, (r0, c0, r1, c1, k) in enumerate(queries):
        if r0 == r1 and c0 == c1:
            best[i] = 0
        else:
            ids.append(i)
    work(0, m - 1, ids)
    return ["YES" if best[i] <= queries[i][4] else "NO" for i in range(q)]


def main():
    data = sys.stdin.read().split()
    pos = 0
    t = int(data[pos]); pos += 1
    out = []
    for _ in range(t):
        n, m, q = int(data[pos]), int(data[pos + 1]), int(data[pos + 2])
        pos += 3
        grid = data[pos:pos + n]
        pos += n
        queries = []
        for _ in range(q):
            queries.append(tuple(int(x) for x in data[pos:pos + 5]))
            pos += 5
        out.extend(solve_case(n, m, grid, queries))
    print("\n".join(out))


if __name__ == "__main__":
    main()