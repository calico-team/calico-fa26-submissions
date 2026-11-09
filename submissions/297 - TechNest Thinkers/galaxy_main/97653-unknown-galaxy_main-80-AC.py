import sys

# Sample input (sirf apne computer par test ke liye): main + bonus dono
SAMPLE = """3
2 4 2
.R.B
.RRB
0 0 1 3
1 0 1 3
2 4 2
.RB.
.RB.
0 0 1 3
0 3 1 3
9 9 3
BR.R.R.R.
BRBRBRBRB
BRBRBRBRB
BRBRBRBRB
BRBRBRBRB
BRBRBRBRB
BRBRBRBRB
BRBRBRBRB
B.B.B.B.B
8 1 8 8
0 4 8 8
8 7 8 8
"""

if len(sys.argv) > 1 and sys.argv[1] == "test":
    data = SAMPLE.split()
else:
    data = sys.stdin.buffer.read().decode().split()


def solve():
    pos = 0
    t = int(data[pos]); pos += 1
    out = []
    for _ in range(t):
        n = int(data[pos]); m = int(data[pos + 1]); q = int(data[pos + 2])
        pos += 3
        grid = data[pos:pos + n]
        pos += n
        # node = (cell * 2 + mode), mode 0 = blue, 1 = red
        parent = list(range(n * m * 2))

        def find(x):
            while parent[x] != x:
                parent[x] = parent[parent[x]]
                x = parent[x]
            return x

        def union(a, b):
            a = find(a)
            b = find(b)
            if a != b:
                parent[a] = b

        # active[mode][cell]
        act = [[False] * (n * m), [False] * (n * m)]
        for i in range(n):
            row = grid[i]
            for j in range(m):
                ch = row[j]
                c = i * m + j
                if ch == '.':
                    act[0][c] = True
                    act[1][c] = True
                    union(c * 2, c * 2 + 1)   # spin
                elif ch == 'B':
                    act[0][c] = True
                else:
                    act[1][c] = True

        for mode in range(2):
            a = act[mode]
            for i in range(n):
                for j in range(m):
                    c = i * m + j
                    if not a[c]:
                        continue
                    if j + 1 < m and a[c + 1]:
                        union(c * 2 + mode, (c + 1) * 2 + mode)
                    if i + 1 < n and a[c + m]:
                        union(c * 2 + mode, (c + m) * 2 + mode)

        for _ in range(q):
            rs = int(data[pos]); cs = int(data[pos + 1])
            re_ = int(data[pos + 2]); ce = int(data[pos + 3])
            pos += 4
            s = find((rs * m + cs) * 2)      # start: blue mode
            e = re_ * m + ce
            ok = False
            for mode in range(2):
                if act[mode][e] and find(e * 2 + mode) == s:
                    ok = True
                    break
            out.append("YES" if ok else "NO")
    print("\n".join(out))


solve()