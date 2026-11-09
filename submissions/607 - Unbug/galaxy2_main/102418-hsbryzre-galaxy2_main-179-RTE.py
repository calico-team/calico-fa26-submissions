import sys

def solve(N, M, Q, G, start, end, K):
    def bfs(sr, sc, sm):
        d = {(sr, sc, sm): 0}
        q = [(sr, sc, sm)]
        for r, c, m in q:
            cur_d = d[(r, c, m)]
            if G[r][c] == '.' and (r, c, 1 - m) not in d:
                d[(r, c, 1 - m)] = cur_d + 1
                q.append((r, c, 1 - m))
            ok = ('.', 'B') if m == 0 else ('.', 'R')
            for dr, dc in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                nr, nc = r + dr, c + dc
                if 0 <= nr < N and 0 <= nc < M and G[nr][nc] in ok and (nr, nc, m) not in d:
                    d[(nr, nc, m)] = cur_d + 1
                    q.append((nr, nc, m))
        return d

    ans = [float('inf')] * Q

    def dc(l, r, q_list):
        if l > r or not q_list:
            return
        mid = (l + r) // 2

        dists = []
        for row in range(N):
            for m in (0, 1):
                ok = ('.', 'B') if m == 0 else ('.', 'R')
                if G[row][mid] in ok:
                    dists.append(bfs(row, mid, m))

        left_q, right_q = [], []
        for i in q_list:
            (sr, sc), (er, ec) = start[i], end[i]
            if min(sc, ec) <= mid <= max(sc, ec):
                best = float('inf')
                for d in dists:
                    d_start = d.get((sr, sc, 0), float('inf'))
                    d_end = min(d.get((er, ec, 0), float('inf')), d.get((er, ec, 1), float('inf')))
                    if d_start + d_end < best:
                        best = d_start + d_end
                ans[i] = best
            elif max(sc, ec) < mid:
                left_q.append(i)
            else:
                right_q.append(i)

        dc(l, mid - 1, left_q)
        dc(mid + 1, r, right_q)

    dc(0, M - 1, list(range(Q)))
    return ['YES' if ans[i] <= K[i] else 'NO' for i in range(Q)]


def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return

    iterator = iter(input_data)
    T = int(next(iterator))
    out = []

    for _ in range(T):
        N = int(next(iterator))
        M = int(next(iterator))
        Q = int(next(iterator))
        G = [next(iterator) for _ in range(N)]
        start, end, K = [], [], []
        for _ in range(Q):
            sr = int(next(iterator))
            sc = int(next(iterator))
            er = int(next(iterator))
            ec = int(next(iterator))
            k = int(next(iterator))
            start.append((sr, sc))
            end.append((er, ec))
            K.append(k)
        out.extend(solve(N, M, Q, G, start, end, K))

    print('\n'.join(out))


if __name__ == '__main__':
    main()