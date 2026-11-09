from operator import add


def solve(N, M, Q, G, start, end, K):
    """
    Graph: node = (row, col, mode), mode 0 = blue, 1 = red. Undirected, unit weights
    (move to an adjacent active tile in the same mode, or spin on a '.' tile).
    Divide & conquer over columns: for a column range [l, r] with middle column m,
    run a multi-source (bit-parallel) BFS from every node of column m restricted to
    [l, r]. Every query lying inside [l, r] is evaluated through column m. A query is
    evaluated in every range containing both endpoints; the smallest range containing
    its whole shortest path always yields the exact distance.
    """
    W = 2 * N
    total = W * M
    active = [False] * total
    for c in range(M):
        for r in range(N):
            ch = G[r][c]
            b = c * W + r * 2
            if ch == '.':
                active[b] = active[b + 1] = True
            elif ch == 'B':
                active[b] = True
            else:
                active[b + 1] = True
    adj = [None] * total
    for c in range(M):
        for r in range(N):
            for mode in (0, 1):
                v = c * W + r * 2 + mode
                if not active[v]:
                    adj[v] = ()
                    continue
                a = []
                if r > 0 and active[v - 2]:
                    a.append(v - 2)
                if r + 1 < N and active[v + 2]:
                    a.append(v + 2)
                if c > 0 and active[v - W]:
                    a.append(v - W)
                if c + 1 < M and active[v + W]:
                    a.append(v + W)
                if G[r][c] == '.':
                    a.append(v ^ 1)
                adj[v] = a

    INF = 1 << 30
    best = [INF] * Q
    ans = [None] * Q
    seen = [0] * total
    need = bytearray(total)

    qs = []
    for i in range(Q):
        (sr, sc), (er, ec) = start[i], end[i]
        s0 = sc * W + sr * 2
        e0 = ec * W + er * 2
        if not active[s0] or K[i] < abs(sc - ec) + abs(sr - er):
            ans[i] = "NO"
            continue
        qs.append((min(sc, ec), max(sc, ec), i, s0, e0))

    stack = [(0, M - 1, qs)]
    while stack:
        l, r, ql = stack.pop()
        if not ql:
            continue
        mid = (l + r) >> 1
        lo_id, hi_id = l * W, (r + 1) * W
        src = [v for v in range(mid * W, mid * W + W) if active[v]]
        k = len(src)
        if k:
            for _, _, _, s0, e0 in ql:
                need[s0] = 1
                if active[e0]:
                    need[e0] = 1
                if active[e0 + 1]:
                    need[e0 + 1] = 1
            rec = {}
            frontier = {}
            for j, v in enumerate(src):
                bit = 1 << j
                seen[v] |= bit
                frontier[v] = bit
                if need[v]:
                    rec.setdefault(v, []).append((0, bit))
            d = 0
            while frontier:
                d += 1
                nxt = {}
                for v, bits in frontier.items():
                    for u in adj[v]:
                        if u < lo_id or u >= hi_id:
                            continue
                        nb = bits & ~seen[u]
                        if nb:
                            seen[u] |= nb
                            if u in nxt:
                                nxt[u] |= nb
                            else:
                                nxt[u] = nb
                if True:
                    for u, nb in nxt.items():
                        if need[u]:
                            rec.setdefault(u, []).append((d, nb))
                frontier = nxt
            cache = {}

            def arr(u):
                a = cache.get(u)
                if a is None:
                    a = [INF] * k
                    for dd, nb in rec.get(u, ()):
                        while nb:
                            lb = nb & -nb
                            a[lb.bit_length() - 1] = dd
                            nb ^= lb
                    cache[u] = a
                return a

            for _, _, i, s0, e0 in ql:
                a = arr(s0)
                if active[e0]:
                    b0 = arr(e0)
                    if active[e0 + 1]:
                        b1 = arr(e0 + 1)
                        t = min(map(add, a, map(min, b0, b1)))
                    else:
                        t = min(map(add, a, b0))
                elif active[e0 + 1]:
                    t = min(map(add, a, arr(e0 + 1)))
                else:
                    t = INF
                if t < best[i]:
                    best[i] = t
            # cleanup
            seen[lo_id:hi_id] = [0] * (hi_id - lo_id)
            for _, _, _, s0, e0 in ql:
                need[s0] = 0
                need[e0] = 0
                need[e0 + 1] = 0
        left, right = [], []
        for item in ql:
            lo, hi, i = item[0], item[1], item[2]
            if best[i] <= K[i]:
                continue
            if hi < mid:
                left.append(item)
            elif lo > mid:
                right.append(item)
        if left:
            stack.append((l, mid - 1, left))
        if right:
            stack.append((mid + 1, r, right))

    return [ans[i] if ans[i] else ("YES" if best[i] <= K[i] else "NO") for i in range(Q)]

def main():
    T = int(input())
    for _ in range(T):
        N, M, Q = map(int, input().split())
        G = []
        for _ in range(N):
            G.append(input())
        start, end, K = [], [], []
        for _ in range(Q):
            start_row, start_col, end_row, end_col, k = map(int, input().split())
            start.append((start_row, start_col))
            end.append((end_row, end_col))
            K.append(k)
        for s in solve(N, M, Q, G, start, end, K):
            print(s)

if __name__ == '__main__':
    main()
