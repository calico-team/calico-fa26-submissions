import sys
from collections import deque


def main():
    data = sys.stdin.read().split()
    pos = 0
    t = int(data[pos]); pos += 1
    out = []

    for _ in range(t):
        n = int(data[pos]); m = int(data[pos + 1]); q = int(data[pos + 2])
        pos += 3
        grid = []
        for _ in range(n):
            grid.append(data[pos])
            pos += 1


        def active(r, c, mode):
            ch = grid[r][c]
            if ch == '.':
                return True
            if ch == 'B':
                return mode == 0
            return mode == 1  # ch == 'R'

        comp = [-1] * (n * m * 2)
        comp_id = 0
        dirs = ((1, 0), (-1, 0), (0, 1), (0, -1))

        for r0 in range(n):
            for c0 in range(m):
                for mode0 in (0, 1):
                    s0 = (r0 * m + c0) * 2 + mode0
                    if comp[s0] != -1 or not active(r0, c0, mode0):
                        continue
                    comp[s0] = comp_id
                    dq = deque([(r0, c0, mode0)])
                    while dq:
                        r, c, mode = dq.popleft()
                        # move to a neighbour in the same mode
                        for dr, dc in dirs:
                            nr, nc = r + dr, c + dc
                            if 0 <= nr < n and 0 <= nc < m and active(nr, nc, mode):
                                idx = (nr * m + nc) * 2 + mode
                                if comp[idx] == -1:
                                    comp[idx] = comp_id
                                    dq.append((nr, nc, mode))
                        # spin (only on a normal tile)
                        if grid[r][c] == '.':
                            idx = (r * m + c) * 2 + (1 - mode)
                            if comp[idx] == -1:
                                comp[idx] = comp_id
                                dq.append((r, c, 1 - mode))
                    comp_id += 1

        for _ in range(q):
            rs = int(data[pos]); cs = int(data[pos + 1])
            re = int(data[pos + 2]); ce = int(data[pos + 3])
            pos += 4
            start_comp = comp[(rs * m + cs) * 2 + 0]  # start in blue mode
            e_blue = comp[(re * m + ce) * 2 + 0]
            e_red = comp[(re * m + ce) * 2 + 1]
            if start_comp != -1 and (start_comp == e_blue or start_comp == e_red):
                out.append("YES")
            else:
                out.append("NO")

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()