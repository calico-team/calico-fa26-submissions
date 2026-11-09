import sys


def main():
    data = sys.stdin.buffer.read().split()
    idx = 0
    T = int(data[idx]); idx += 1
    out = []
    INF = 10 ** 9
    for _ in range(T):
        N, M, Q = int(data[idx]), int(data[idx + 1]), int(data[idx + 2]); idx += 3
        grid = [data[idx + i].decode() for i in range(N)]; idx += N
        # active[mode][r][c]: mode 0 = blue, 1 = red
        active = [[[ch == '.' or ch == 'B' for ch in row] for row in grid],
                  [[ch == '.' or ch == 'R' for ch in row] for row in grid]]
        sawal = []
        best = [INF] * Q
        list0 = []
        for i in range(Q):
            sr, sc, er, ec, k = (int(x) for x in data[idx:idx + 5]); idx += 5
            sawal.append((sr, sc, er, ec, k))
            if sr == er and sc == ec:
                best[i] = 0
            else:
                list0.append(i)

        # stack se divide and conquer (recursion ke baghair)
        stack = [(0, M - 1, list0)]
        while stack:
            l, r, lst = stack.pop()
            if l > r or not lst:
                continue
            mid = (l + r) // 2
            W = r - l + 1
            S = N * W * 2
            # state id = (row*W + (col-l))*2 + mode; padosi pehle se bana lo
            nbrs = [None] * S
            for row in range(N):
                for c in range(l, r + 1):
                    base = (row * W + (c - l)) * 2
                    dot = grid[row][c] == '.'
                    for m in (0, 1):
                        if not active[m][row][c]:
                            continue
                        lst_n = []
                        for nr, nc in ((row + 1, c), (row - 1, c), (row, c + 1), (row, c - 1)):
                            if 0 <= nr < N and l <= nc <= r and active[m][nr][nc]:
                                lst_n.append((nr * W + (nc - l)) * 2 + m)
                        if dot:
                            lst_n.append(base + 1 - m)  # spin
                        nbrs[base + m] = lst_n
            # har query ke start aur end states
            qs = []
            for qi in lst:
                sr, sc, er, ec, k = sawal[qi]
                a = (sr * W + (sc - l)) * 2  # start blue mode
                eb = (er * W + (ec - l)) * 2
                ends = [eb + m for m in (0, 1) if active[m][er][ec]]
                qs.append((qi, a, ends))
            for row in range(N):
                for m in (0, 1):
                    if not active[m][row][mid]:
                        continue
                    src = (row * W + (mid - l)) * 2 + m
                    dist = [INF] * S
                    dist[src] = 0
                    q = [src]
                    for s in q:  # list badhti rehti hai, ye BFS queue ka kaam karti hai
                        d1 = dist[s] + 1
                        for t in nbrs[s]:
                            if dist[t] == INF:
                                dist[t] = d1
                                q.append(t)
                    for qi, a, ends in qs:
                        da = dist[a]
                        if da == INF:
                            continue
                        db = min([dist[e] for e in ends], default=INF)
                        if db != INF and da + db < best[qi]:
                            best[qi] = da + db
            left, right = [], []
            for qi in lst:
                sc, ec = sawal[qi][1], sawal[qi][3]
                if sc < mid and ec < mid:
                    left.append(qi)
                elif sc > mid and ec > mid:
                    right.append(qi)
            stack.append((l, mid - 1, left))
            stack.append((mid + 1, r, right))
        for i in range(Q):
            out.append("YES" if best[i] <= sawal[i][4] else "NO")
    print("\n".join(out))


main()