import sys
from collections import deque

input = sys.stdin.readline

def solve():
    t = int(input())

    for _ in range(t):
        n, m, q = map(int, input().split())
        g = [input().strip() for _ in range(n)]

        dx = (1, -1, 0, 0)
        dy = (0, 0, 1, -1)

        def idx(r, c, s):
            return 2 * (r * m + c) + s

        def ok(r, c, s):
            if not (0 <= r < n and 0 <= c < m):
                return False
            return g[r][c] == '.' or \
                   (g[r][c] == 'B' and s == 0) or \
                   (g[r][c] == 'R' and s == 1)

        vis = [-1] * (2 * n * m)
        cc = 0

        for r in range(n):
            for c in range(m):
                for s in range(2):
                    st = idx(r, c, s)

                    if not ok(r, c, s) or vis[st] != -1:
                        continue

                    vis[st] = cc
                    qu = deque([st])

                    while qu:
                        v = qu.popleft()
                        mode = v & 1
                        pos = v >> 1
                        x, y = divmod(pos, m)

                        for k in range(4):
                            nx = x + dx[k]
                            ny = y + dy[k]

                            if not ok(nx, ny, mode):
                                continue

                            u = idx(nx, ny, mode)

                            if vis[u] == -1:
                                vis[u] = cc
                                qu.append(u)

                        if g[x][y] == '.':
                            u = v ^ 1

                            if vis[u] == -1:
                                vis[u] = cc
                                qu.append(u)

                    cc += 1

        ans = []

        for _ in range(q):
            rs, cs, re, ce = map(int, input().split())

            a = vis[idx(rs, cs, 0)]
            b = vis[idx(re, ce, 0)]
            c = vis[idx(re, ce, 1)]

            ans.append("YES" if a == b or a == c else "NO")

        sys.stdout.write("\n".join(ans) + "\n")


if __name__ == "__main__":
    solve()