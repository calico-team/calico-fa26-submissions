import sys


def solve(N, M, Q, G, start, end):
    """
    Reachability on a 2-layer graph: node (cell, mode), mode 0 = blue, 1 = red.
    Walk between adjacent cells active in the current mode; spin (toggle mode)
    only on a normal '.' cell. A query is YES iff the destination cell, in some
    mode, is in the same connected component as the start (always blue mode).
    """
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
        ra, rb = find(a), find(b)
        if ra != rb:
            parent[ra] = rb

    # active[mode][cell]: can stand there in that mode
    # blue (0): '.' or 'B';  red (1): '.' or 'R'
    rows = G

    def active_blue(ch):
        return ch == '.' or ch == 'B'

    def active_red(ch):
        return ch == '.' or ch == 'R'

    for r in range(N):
        row = rows[r]
        base = r * M
        for c in range(M):
            ch = row[c]
            cell = base + c
            ab = (ch == '.' or ch == 'B')
            ar = (ch == '.' or ch == 'R')
            # spin on normal tile links the two modes
            if ch == '.':
                union(cell, NM + cell)
            # right neighbor
            if c + 1 < M:
                ch2 = row[c + 1]
                cell2 = cell + 1
                if ab and (ch2 == '.' or ch2 == 'B'):
                    union(cell, cell2)
                if ar and (ch2 == '.' or ch2 == 'R'):
                    union(NM + cell, NM + cell2)
            # down neighbor
            if r + 1 < N:
                ch3 = rows[r + 1][c]
                cell3 = cell + M
                if ab and (ch3 == '.' or ch3 == 'B'):
                    union(cell, cell3)
                if ar and (ch3 == '.' or ch3 == 'R'):
                    union(NM + cell, NM + cell3)

    res = []
    for i in range(Q):
        rs, cs = start[i]
        re, ce = end[i]
        s_node = rs * M + cs                 # start is normal -> blue layer
        root_s = find(s_node)
        ecell = re * M + ce
        ch = rows[re][ce]
        ok = False
        if (ch == '.' or ch == 'B') and find(ecell) == root_s:
            ok = True
        elif (ch == '.' or ch == 'R') and find(NM + ecell) == root_s:
            ok = True
        res.append("YES" if ok else "NO")
    return res


def main():
    data = sys.stdin.buffer.read().split()
    idx = 0
    T = int(data[idx]); idx += 1
    out = []
    for _ in range(T):
        N = int(data[idx]); M = int(data[idx + 1]); Q = int(data[idx + 2]); idx += 3
        G = [data[idx + r].decode() for r in range(N)]; idx += N
        start = []
        end = []
        for _ in range(Q):
            rs = int(data[idx]); cs = int(data[idx + 1]); re = int(data[idx + 2]); ce = int(data[idx + 3]); idx += 4
            start.append((rs, cs))
            end.append((re, ce))
        out.extend(solve(N, M, Q, G, start, end))
    sys.stdout.write('\n'.join(out) + '\n')


if __name__ == '__main__':
    main()
