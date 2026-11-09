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
    NM = N * M
    # state id = mode * NM + r * M + c   (mode 0 = blue, mode 1 = red)
    comp = [-1] * (2 * NM)

    def active(r, c, mode):
        ch = G[r][c]
        return ch == '.' or (ch == 'B' and mode == 0) or (ch == 'R' and mode == 1)

    label = 0
    for mode in range(2):
        for r in range(N):
            for c in range(M):
                sid = mode * NM + r * M + c
                if comp[sid] != -1 or not active(r, c, mode):
                    continue
                comp[sid] = label
                stack = [(r, c, mode)]
                while stack:
                    cr, cc, cm = stack.pop()
                    # walk to neighbours in the same mode
                    for nr, nc in ((cr + 1, cc), (cr - 1, cc), (cr, cc + 1), (cr, cc - 1)):
                        if 0 <= nr < N and 0 <= nc < M and active(nr, nc, cm):
                            nid = cm * NM + nr * M + nc
                            if comp[nid] == -1:
                                comp[nid] = label
                                stack.append((nr, nc, cm))
                    # spin on a normal tile
                    if G[cr][cc] == '.':
                        om = 1 - cm
                        oid = om * NM + cr * M + cc
                        if comp[oid] == -1:
                            comp[oid] = label
                            stack.append((cr, cc, om))
                label += 1

    ans = []
    for i in range(Q):
        sr, sc = start[i]
        er, ec = end[i]
        a = comp[sr * M + sc]  # start is normal, blue mode
        ch = G[er][ec]
        if ch == 'R':
            b = comp[NM + er * M + ec]
        else:  # 'B' or '.'
            b = comp[er * M + ec]
        ans.append("YES" if a != -1 and a == b else "NO")
    return ans

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