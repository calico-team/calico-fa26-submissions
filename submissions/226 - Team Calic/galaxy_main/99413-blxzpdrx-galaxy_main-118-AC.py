def solve(N: int, M: int, Q: int, G: list[str], start: list[tuple[int, int]], end: list[tuple[int, int]]) -> list[str]:
    """
    Return an array of Q strings, the i-th of which is "YES"
    if Big Ben can travel from start[i] to end[i], and "NO"
    otherwise.

    N: the number of rows in the grid
    M: the number of columns in the grid
    Q: the number of queries
    G: the grid, where each tile is 'R', 'B', or '.'
    start: the (row, column) of the starting tile of each query
    end: the (row, column) of the ending tile of each query
    """
    def active(r, c, mode):
        ch = G[r][c]
        if ch == '.':
            return True
        return (ch == 'B' and mode == 0) or (ch == 'R' and mode == 1)

    comp = [-1] * (N * M * 2)
    cid = 0
    dirs = ((1, 0), (-1, 0), (0, 1), (0, -1))

    for r in range(N):
        for c in range(M):
            for mode in (0, 1):
                s = (r * M + c) * 2 + mode
                if comp[s] != -1 or not active(r, c, mode):
                    continue
                comp[s] = cid
                queue = [(r, c, mode)]
                head = 0
                while head < len(queue):
                    cr, cc, cm = queue[head]
                    head += 1
                    # walk to neighbors in the same mode
                    for dr, dc in dirs:
                        nr, nc = cr + dr, cc + dc
                        if 0 <= nr < N and 0 <= nc < M and active(nr, nc, cm):
                            ns = (nr * M + nc) * 2 + cm
                            if comp[ns] == -1:
                                comp[ns] = cid
                                queue.append((nr, nc, cm))
                    # spin on a normal tile
                    if G[cr][cc] == '.':
                        ns = (cr * M + cc) * 2 + (1 - cm)
                        if comp[ns] == -1:
                            comp[ns] = cid
                            queue.append((cr, cc, 1 - cm))
                cid += 1

    res = []
    for i in range(Q):
        sr, sc = start[i]
        er, ec = end[i]
        s_state = (sr * M + sc) * 2 + 0  # start is always in blue mode
        ch = G[er][ec]
        e_mode = 1 if ch == 'R' else 0   # normal tile: both modes are connected via spin
        e_state = (er * M + ec) * 2 + e_mode
        if comp[s_state] != -1 and comp[s_state] == comp[e_state]:
            res.append("YES")
        else:
            res.append("NO")
    return res

def main():
    T = int(input())
    for _ in range(T):
        N, M, Q = map(int, input().split())
        G = []
        for _ in range(N):
            G.append(input())
        start, end = [], []
        for _ in range(Q):
            start_row, start_col, end_row, end_col = map(int, input().split())
            start.append((start_row, start_col))
            end.append((end_row, end_col))
        for s in solve(N, M, Q, G, start, end):
            print(s)

if __name__ == '__main__':
    main()
