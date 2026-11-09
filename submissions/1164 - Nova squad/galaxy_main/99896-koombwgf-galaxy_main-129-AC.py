import sys
from collections import deque

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
8 7 8 8"""

def read_input():
    try:
        text = sys.stdin.read()
    except Exception:
        text = ""
    return text if text.strip() else SAMPLE

def main():
    data = read_input().split()
    idx = 0
    T = int(data[idx]); idx += 1
    out = []
    for _ in range(T):
        n, m, q = int(data[idx]), int(data[idx+1]), int(data[idx+2]); idx += 3
        g = data[idx:idx+n]; idx += n

        def active(r, c, mode):          # mode 0 = blue, 1 = red
            ch = g[r][c]
            return ch == '.' or (ch == 'B' and mode == 0) or (ch == 'R' and mode == 1)

        comp = [-1] * (n * m * 2)
        cid = 0
        for r in range(n):
            for c in range(m):
                for mode in (0, 1):
                    s = (r * m + c) * 2 + mode
                    if comp[s] != -1 or not active(r, c, mode):
                        continue
                    comp[s] = cid
                    dq = deque([(r, c, mode)])
                    while dq:
                        x, y, md = dq.popleft()
                        # spin on a normal tile
                        if g[x][y] == '.':
                            t = (x * m + y) * 2 + (1 - md)
                            if comp[t] == -1:
                                comp[t] = cid
                                dq.append((x, y, 1 - md))
                        # walk to neighbours in the same mode
                        for dx, dy in ((1,0),(-1,0),(0,1),(0,-1)):
                            nx, ny = x + dx, y + dy
                            if 0 <= nx < n and 0 <= ny < m and active(nx, ny, md):
                                t = (nx * m + ny) * 2 + md
                                if comp[t] == -1:
                                    comp[t] = cid
                                    dq.append((nx, ny, md))
                    cid += 1

        for _ in range(q):
            rs, cs, re, ce = (int(v) for v in data[idx:idx+4]); idx += 4
            start = comp[(rs * m + cs) * 2 + 0]      # start in blue mode
            ok = False
            for mode in (0, 1):
                if active(re, ce, mode) and comp[(re * m + ce) * 2 + mode] == start:
                    ok = True
                    break
            out.append("YES" if ok else "NO")

    print("\n".join(out))

main()