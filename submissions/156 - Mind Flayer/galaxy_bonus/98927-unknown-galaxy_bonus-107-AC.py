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
    g = [row.strip() for row in G]
    par = list(range(2 * N * M))

    def find(x):
        while par[x] != x:
            par[x] = par[par[x]]
            x = par[x]
        return x

    def union(a, b):
        a = find(a)
        b = find(b)
        if a != b:
            par[a] = b

    def active(ch, mode):
        return ch == '.' or (ch == 'B' and mode == 0) or (ch == 'R' and mode == 1)

    for r in range(N):
        row = g[r]
        for c in range(M):
            ch = row[c]
            cell = r * M + c
            if ch == '.':
                union(cell * 2, cell * 2 + 1)
            for mode in (0, 1):
                if not active(ch, mode):
                    continue
                if c + 1 < M and active(row[c + 1], mode):
                    union(cell * 2 + mode, (cell + 1) * 2 + mode)
                if r + 1 < N and active(g[r + 1][c], mode):
                    union(cell * 2 + mode, (cell + M) * 2 + mode)

    ans = []
    for i in range(Q):
        rs, cs = start[i]
        re, ce = end[i]
        dmode = 1 if g[re][ce] == 'R' else 0
        a = find((rs * M + cs) * 2)
        b = find((re * M + ce) * 2 + dmode)
        ans.append("YES" if a == b else "NO")
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