import sys

def main():
    data = sys.stdin.read().split()
    pos = 0
    t = int(data[pos]); pos += 1
    out = []
    for _ in range(t):
        n = int(data[pos]); m = int(data[pos + 1]); q = int(data[pos + 2]); pos += 3
        grid = data[pos:pos + n]; pos += n
        parent = list(range(2 * n * m))

        def find(x):
            while parent[x] != x:
                parent[x] = parent[parent[x]]
                x = parent[x]
            return x

        def union(a, b):
            a = find(a); b = find(b)
            if a != b:
                parent[a] = b

        # node id = (r*m + c)*2 + mode, mode 0 = blue, mode 1 = red
        for r in range(n):
            row = grid[r]
            for c in range(m):
                ch = row[c]
                i = (r * m + c) * 2
                a0 = ch != 'R'
                a1 = ch != 'B'
                if ch == '.':
                    union(i, i + 1)
                if c + 1 < m:
                    ch2 = row[c + 1]
                    j = i + 2
                    if a0 and ch2 != 'R':
                        union(i, j)
                    if a1 and ch2 != 'B':
                        union(i + 1, j + 1)
                if r + 1 < n:
                    ch2 = grid[r + 1][c]
                    j = i + 2 * m
                    if a0 and ch2 != 'R':
                        union(i, j)
                    if a1 and ch2 != 'B':
                        union(i + 1, j + 1)

        for _ in range(q):
            rs = int(data[pos]); cs = int(data[pos + 1])
            re = int(data[pos + 2]); ce = int(data[pos + 3]); pos += 4
            a = (rs * m + cs) * 2
            b = (re * m + ce) * 2 + (1 if grid[re][ce] == 'R' else 0)
            out.append("YES" if find(a) == find(b) else "NO")
    print("\n".join(out))

if __name__ == "__main__":
    main()
