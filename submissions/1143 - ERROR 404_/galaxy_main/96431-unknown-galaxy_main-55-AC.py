import sys
from collections import deque

def solve() -> None:
    data = sys.stdin.buffer.read().split()
    it = iter(data)
    t = int(next(it, 0))
    out = []
    for _ in range(t):
        n = int(next(it)); m = int(next(it)); q = int(next(it))
        grid = []
        for _ in range(n):
            row = next(it).decode()
            # in case rows split, they are tokens without spaces, fine
            while len(row) < m:
                # if row was split char by char (should not happen)
                row += next(it).decode()
            grid.append(row)

        # comp[r][c][mode] = -1 unvisited
        comp = [[[-1, -1] for _ in range(m)] for _ in range(n)]

        def active(r, c, mode):
            ch = grid[r][c]
            if ch == '.':
                return True
            if mode == 0:  # blue
                return ch == 'B'
            else:  # red
                return ch == 'R'

        cid = 0
        dirs = [(1, 0), (-1, 0), (0, 1), (0, -1)]
        for sr in range(n):
            for sc in range(m):
                for sm in (0, 1):
                    if not active(sr, sc, sm):
                        continue
                    if comp[sr][sc][sm] != -1:
                        continue
                    # BFS
                    dq = deque()
                    dq.append((sr, sc, sm))
                    comp[sr][sc][sm] = cid
                    while dq:
                        r, c, mode = dq.popleft()
                        # spin
                        if grid[r][c] == '.':
                            nm = 1 - mode
                            if comp[r][c][nm] == -1:
                                comp[r][c][nm] = cid
                                dq.append((r, c, nm))
                        # moves
                        for dr, dc in dirs:
                            nr, nc = r + dr, c + dc
                            if 0 <= nr < n and 0 <= nc < m:
                                if comp[nr][nc][mode] == -1 and active(nr, nc, mode):
                                    comp[nr][nc][mode] = cid
                                    dq.append((nr, nc, mode))
                    cid += 1

        for _ in range(q):
            rs = int(next(it)); cs = int(next(it)); re = int(next(it)); ce = int(next(it))
            start_c = comp[rs][cs][0]  # start in blue mode, start is '.'
            ok = False
            if start_c != -1:
                ch = grid[re][ce]
                if ch == '.':
                    if comp[re][ce][0] == start_c or comp[re][ce][1] == start_c:
                        ok = True
                elif ch == 'B':
                    if comp[re][ce][0] == start_c:
                        ok = True
                elif ch == 'R':
                    if comp[re][ce][1] == start_c:
                        ok = True
            out.append("YES" if ok else "NO")
    sys.stdout.write("\n".join(out))

if __name__ == "__main__":
    solve()