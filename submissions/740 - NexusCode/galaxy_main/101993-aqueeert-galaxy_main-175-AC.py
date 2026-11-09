import sys


def solve(N, M, Q, G, start, end):
    NM = N * M
    parent = list(range(2 * NM))

    def find(x):
        root = x
        while parent[root] != root:
            root = parent[root]
        while parent[x] != root:
            parent[x], x = root, parent[x]
        return root

    def union(a, b):
        a = find(a)
        b = find(b)
        if a != b:
            parent[a] = b

    # layer 0 (blue mode): normal + B tiles; layer 1 (red mode): normal + R tiles
    for r in range(N):
        row = G[r]
        for c in range(M):
            ch = row[c]
            i = r * M + c
            if ch == '.':
                union(i, NM + i)  # free mode toggle on normal tiles
            blue = ch != 'R'
            red = ch != 'B'
            if c + 1 < M:
                nch = row[c + 1]
                if blue and nch != 'R':
                    union(i, i + 1)
                if red and nch != 'B':
                    union(NM + i, NM + i + 1)
            if r + 1 < N:
                nch = G[r + 1][c]
                if blue and nch != 'R':
                    union(i, i + M)
                if red and nch != 'B':
                    union(NM + i, NM + i + M)

    res = []
    for (sr, sc), (er, ec) in zip(start, end):
        s = find(sr * M + sc)
        e = er * M + ec
        if G[er][ec] == 'R':
            e += NM
        res.append("YES" if find(e) == s else "NO")
    return res


def main():
    data = sys.stdin.read().split()
    pos = 0
    T = int(data[pos]); pos += 1
    out = []
    for _ in range(T):
        N = int(data[pos]); M = int(data[pos + 1]); Q = int(data[pos + 2]); pos += 3
        G = data[pos:pos + N]; pos += N
        start, end = [], []
        for _ in range(Q):
            start.append((int(data[pos]), int(data[pos + 1])))
            end.append((int(data[pos + 2]), int(data[pos + 3])))
            pos += 4
        out.extend(solve(N, M, Q, G, start, end))
    print("\n".join(out))


if __name__ == '__main__':
    main()