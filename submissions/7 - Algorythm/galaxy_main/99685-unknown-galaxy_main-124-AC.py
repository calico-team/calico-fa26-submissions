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
    # State = (cell, mode); mode 0 = blue, 1 = red.
    # Moves and spins are reversible, so the state graph is undirected -> DSU.
    parent = list(range(2 * N * M))

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

    def active(r, c, mode):
        ch = G[r][c]
        if ch == '.':
            return True
        if ch == 'B':
            return mode == 0
        return mode == 1  # 'R'

    for r in range(N):
        for c in range(M):
            # spin on normal tile
            if G[r][c] == '.':
                union((r * M + c) * 2, (r * M + c) * 2 + 1)
            for mode in (0, 1):
                if not active(r, c, mode):
                    continue
                u = (r * M + c) * 2 + mode
                if c + 1 < M and active(r, c + 1, mode):
                    union(u, (r * M + c + 1) * 2 + mode)
                if r + 1 < N and active(r + 1, c, mode):
                    union(u, ((r + 1) * M + c) * 2 + mode)

    res = []
    for i in range(Q):
        sr, sc = start[i]
        er, ec = end[i]
        s = find((sr * M + sc) * 2 + 0)  # start in blue mode
        e0 = find((er * M + ec) * 2 + 0)
        e1 = find((er * M + ec) * 2 + 1)
        # inactive states are isolated nodes, so they never match s
        ok = (s == e0 and active(er, ec, 0)) or (s == e1 and active(er, ec, 1))
        res.append("YES" if ok else "NO")
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