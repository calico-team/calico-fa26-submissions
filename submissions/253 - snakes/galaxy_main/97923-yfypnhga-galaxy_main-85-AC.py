import sys

def main():
    data = sys.stdin.buffer.read().split()
    pos = 0
    T = int(data[pos]); pos += 1
    out = []
    for _ in range(T):
        N = int(data[pos]); M = int(data[pos + 1]); Q = int(data[pos + 2]); pos += 3
        rows = []
        for _ in range(N):
            rows.append(data[pos].decode()); pos += 1
        g = ''.join(rows)
        total = N * M
        # if youre standing on R you have to be in red mode, on B you have to be in blue mode,
        # and on a . you can spin whenever you want. so the mode kind of sorts itself out and the
        # only step that can ever actually be blocked is going from R straight onto B (or B onto R)
        comp = [-1] * total
        cid = 0
        for s in range(total):
            if comp[s] != -1:
                continue
            comp[s] = cid
            stack = [s]
            while stack:
                u = stack.pop()
                r, c = divmod(u, M)
                cu = g[u]
                # 4 neighbors, same check each time: skip it if its R next to B, otherwise its walkable
                if r > 0:
                    v = u - M
                    if comp[v] == -1:
                        cv = g[v]
                        if not ((cu == 'R' and cv == 'B') or (cu == 'B' and cv == 'R')):
                            comp[v] = cid; stack.append(v)
                if r + 1 < N:
                    v = u + M
                    if comp[v] == -1:
                        cv = g[v]
                        if not ((cu == 'R' and cv == 'B') or (cu == 'B' and cv == 'R')):
                            comp[v] = cid; stack.append(v)
                if c > 0:
                    v = u - 1
                    if comp[v] == -1:
                        cv = g[v]
                        if not ((cu == 'R' and cv == 'B') or (cu == 'B' and cv == 'R')):
                            comp[v] = cid; stack.append(v)
                if c + 1 < M:
                    v = u + 1
                    if comp[v] == -1:
                        cv = g[v]
                        if not ((cu == 'R' and cv == 'B') or (cu == 'B' and cv == 'R')):
                            comp[v] = cid; stack.append(v)
            cid += 1
        for _ in range(Q):
            rs = int(data[pos]); cs = int(data[pos + 1])
            re = int(data[pos + 2]); ce = int(data[pos + 3]); pos += 4
            # start is always a normal tile so starting in blue doesnt matter, we can spin before moving.
            # just need the two cells to be in the same component, works the same whether the end is the corner or not
            out.append("YES" if comp[rs * M + cs] == comp[re * M + ce] else "NO")
    sys.stdout.write("\n".join(out) + "\n")

main()
