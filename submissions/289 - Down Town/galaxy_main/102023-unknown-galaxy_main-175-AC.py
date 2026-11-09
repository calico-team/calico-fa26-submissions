import sys


def main():
    data = sys.stdin.read().split()
    pos = 0
    t = int(data[pos])
    pos += 1
    out = []
    for _ in range(t):
        n = int(data[pos])
        m = int(data[pos + 1])
        q = int(data[pos + 2])
        pos += 3
        g = data[pos : pos + n]
        pos += n

        parent = list(range(2 * n * m))

        def find(x):
            r = x
            while parent[r] != r:
                r = parent[r]
            while parent[x] != r:
                parent[x], x = r, parent[x]
            return r

        def union(a, b):
            ra, rb = find(a), find(b)
            if ra != rb:
                parent[ra] = rb

        def active(ch, mode):
            return ch == "." or (ch == "B" and mode == 0) or (ch == "R" and mode == 1)

        for i in range(n):
            row = g[i]
            for j in range(m):
                ch = row[j]
                c = i * m + j
                if ch == ".":
                    union(2 * c, 2 * c + 1)  # spin
                for mode in (0, 1):
                    if not active(ch, mode):
                        continue
                    if j + 1 < m and active(row[j + 1], mode):
                        union(2 * c + mode, 2 * (c + 1) + mode)
                    if i + 1 < n and active(g[i + 1][j], mode):
                        union(2 * c + mode, 2 * (c + m) + mode)

        for _ in range(q):
            rs = int(data[pos])
            cs = int(data[pos + 1])
            re = int(data[pos + 2])
            ce = int(data[pos + 3])
            pos += 4
            root = find(2 * (rs * m + cs))
            ch = g[re][ce]
            e = re * m + ce
            ok = False
            for mode in (0, 1):
                if active(ch, mode) and find(2 * e + mode) == root:
                    ok = True
                    break
            out.append("YES" if ok else "NO")
    print("\n".join(out))


main()
