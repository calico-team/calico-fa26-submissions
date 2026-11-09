import sys
from collections import deque

def go(N, M, g, qs):
    cache = {}
    res = []

    def bfs(sr, sc):
        BIG = 10**9
        dist = [[[BIG] * M for _ in range(N)] for _ in range(2)]
        dist[0][sr][sc] = 0
        dq = deque([(sr, sc, 0)])
        while dq:
            r, c, m = dq.popleft()
            d = dist[m][r][c]
            if g[r][c] == '.':
                nm = 1 - m
                if dist[nm][r][c] > d + 1:
                    dist[nm][r][c] = d + 1
                    dq.append((r, c, nm))
            for dr, dc in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                nr = r + dr
                nc = c + dc
                if 0 <= nr < N and 0 <= nc < M:
                    ch = g[nr][nc]
                    if (ch == '.' or (ch == 'B' and m == 0) or (ch == 'R' and m == 1)) and dist[m][nr][nc] > d + 1:
                        dist[m][nr][nc] = d + 1
                        dq.append((nr, nc, m))
        return dist

    for rs, cs, re, ce, K in qs:
        key = (rs, cs)
        if key not in cache:
            cache[key] = bfs(rs, cs)
        dist = cache[key]
        ch = g[re][ce]
        if ch == '.':
            best = min(dist[0][re][ce], dist[1][re][ce])
        elif ch == 'B':
            best = dist[0][re][ce]
        else:
            best = dist[1][re][ce]
        res.append("YES" if best <= K else "NO")

    return res

def main():
    d = sys.stdin.read().split()
    p = 0
    T = int(d[p]); p += 1
    out = []
    for _ in range(T):
        N, M, Q = int(d[p]), int(d[p+1]), int(d[p+2])
        p += 3
        g = d[p:p+N]
        p += N
        qs = []
        for _ in range(Q):
            rs = int(d[p]); cs = int(d[p+1]); re = int(d[p+2]); ce = int(d[p+3]); K = int(d[p+4])
            p += 5
            qs.append((rs, cs, re, ce, K))
        out.extend(go(N, M, g, qs))
    sys.stdout.write("\n".join(out))

if __name__ == "__main__":
    main()