import sys


def main():
    data = sys.stdin.buffer.read().split()
    t = int(data[0])
    pos = 1
    out = []
    for _ in range(t):
        n, m, q = int(data[pos]), int(data[pos + 1]), int(data[pos + 2])
        pos += 3
        rows = [data[pos + i].decode() for i in range(n)]
        pos += n
        queries = []
        for _ in range(q):
            rs, cs, re_, ce, k = (int(v) for v in data[pos:pos + 5])
            pos += 5
            queries.append((rs, cs, re_, ce, k))
        out.extend(solve(n, m, rows, queries))
    sys.stdout.write("\n".join(out) + "\n")


def solve(n, m, rows, queries):
    INF = float('inf')
    # mode 0 = blue, mode 1 = red
    normal = [[ch == '.' for ch in row] for row in rows]
    active = [
        [[ch != 'R' for ch in row] for row in rows],   # blue mode
        [[ch != 'B' for ch in row] for row in rows],   # red mode
    ]

    best = [INF] * len(queries)
    # (l, r, list of query ids whose endpoints both lie in columns [l, r])
    stack = [(0, m - 1, list(range(len(queries))))]

    while stack:
        l, r, qids = stack.pop()
        if not qids:
            continue
        w = r - l + 1
        mid = (l + r) // 2
        size = n * w * 2

        # BFS from every valid state on the middle column, restricted to [l, r]
        dists = []
        for row in range(n):
            for mode in (0, 1):
                if not active[mode][row][mid]:
                    continue
                src = (row * w + (mid - l)) * 2 + mode
                dist = [-1] * size
                dist[src] = 0
                bq = [src]
                for v in bq:
                    nd = dist[v] + 1
                    md = v & 1
                    cell = v >> 1
                    rr = cell // w
                    cc = cell - rr * w
                    col = cc + l
                    act = active[md]
                    # spin on a normal tile
                    if normal[rr][col]:
                        u = v ^ 1
                        if dist[u] < 0:
                            dist[u] = nd
                            bq.append(u)
                    if cc > 0 and act[rr][col - 1]:
                        u = v - 2
                        if dist[u] < 0:
                            dist[u] = nd
                            bq.append(u)
                    if cc < w - 1 and act[rr][col + 1]:
                        u = v + 2
                        if dist[u] < 0:
                            dist[u] = nd
                            bq.append(u)
                    if rr > 0 and act[rr - 1][col]:
                        u = v - 2 * w
                        if dist[u] < 0:
                            dist[u] = nd
                            bq.append(u)
                    if rr < n - 1 and act[rr + 1][col]:
                        u = v + 2 * w
                        if dist[u] < 0:
                            dist[u] = nd
                            bq.append(u)
                dists.append(dist)

        left, right = [], []
        for qi in qids:
            rs, cs, re_, ce, _ = queries[qi]
            s_idx = (rs * w + (cs - l)) * 2            # start state: blue mode
            e_idx = (re_ * w + (ce - l)) * 2
            cur = best[qi]
            for dist in dists:
                a = dist[s_idx]
                if a < 0:
                    continue
                b0 = dist[e_idx]
                b1 = dist[e_idx + 1]
                if b0 < 0:
                    if b1 < 0:
                        continue
                    b = b1
                elif b1 < 0 or b0 < b1:
                    b = b0
                else:
                    b = b1
                if a + b < cur:
                    cur = a + b
            best[qi] = cur
            # paths that avoid the middle column stay on one side
            if cs < mid and ce < mid:
                left.append(qi)
            elif cs > mid and ce > mid:
                right.append(qi)

        if left:
            stack.append((l, mid - 1, left))
        if right:
            stack.append((mid + 1, r, right))

    return ["YES" if best[i] <= queries[i][4] else "NO" for i in range(len(queries))]


main()