import sys

def solve():
    it = iter(sys.stdin.buffer.read().split())
    t = int(next(it))
    out = []

    for _ in range(t):
        n, m, q = int(next(it)), int(next(it)), int(next(it))
        g = [next(it).decode() for _ in range(n)]
        size = n * m
        p = list(range(2 * size))
        sz = [1] * (2 * size)

        def find(x):
            while p[x] != x:
                p[x] = p[p[x]]
                x = p[x]
            return x

        def union(a, b):
            a, b = find(a), find(b)
            if a == b:
                return
            if sz[a] < sz[b]:
                a, b = b, a
            p[b] = a
            sz[a] += sz[b]

        # State 0 = blue mode, state 1 = red mode.
        for r in range(n):
            for c in range(m):
                ch = g[r][c]
                x = r * m + c

                if ch == '.':
                    union(x, size + x)  # Spin on a normal tile.

                for mode, tile in ((0, 'B'), (1, 'R')):
                    if ch != '.' and ch != tile:
                        continue
                    u = mode * size + x
                    if c + 1 < m:
                        vch = g[r][c + 1]
                        if vch == '.' or vch == tile:
                            union(u, mode * size + x + 1)
                    if r + 1 < n:
                        vch = g[r + 1][c]
                        if vch == '.' or vch == tile:
                            union(u, mode * size + x + m)

        for _ in range(q):
            rs, cs, re, ce = (int(next(it)) for _ in range(4))
            s = rs * m + cs
            d = re * m + ce
            root = find(s)  # Start in blue mode.
            ch = g[re][ce]
            ok = (ch == '.' and (root == find(d) or root == find(size + d)))
            if ch == 'B':
                ok = root == find(d)
            elif ch == 'R':
                ok = root == find(size + d)
            out.append("YES" if ok else "NO")

    sys.stdout.write("\n".join(out))

if __name__ == "__main__":
    solve()
