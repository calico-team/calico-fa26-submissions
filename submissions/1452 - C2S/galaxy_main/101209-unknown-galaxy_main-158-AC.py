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
    parent = list(range(2 * N * M))

    def find(x):
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x

    def union(a, b):
        a, b = find(a), find(b)
        if a != b:
            parent[a] = b

    def active(ch, mode):
        return ch == '.' or (ch == 'B' and mode == 0) or (ch == 'R' and mode == 1)

    for r in range(N):
        row = G[r]
        for c in range(M):
            ch = row[c]
            base = (r * M + c) * 2
            # spin: normal tile pe dono modes connected
            if ch == '.':
                union(base, base + 1)
            # right aur down neighbours (undirected, isliye itna kaafi hai)
            for dr, dc in ((0, 1), (1, 0)):
                nr, nc = r + dr, c + dc
                if nr < N and nc < M:
                    nch = G[nr][nc]
                    nbase = (nr * M + nc) * 2
                    for mode in (0, 1):
                        if active(ch, mode) and active(nch, mode):
                            union(base + mode, nbase + mode)

    res = []
    for (sr, sc), (er, ec) in zip(start, end):
        s = find((sr * M + sc) * 2 + 0)  # start: blue mode
        ch = G[er][ec]
        eb = (er * M + ec) * 2
        ok = False
        # end tile jis mode mein active hai, usi node ko check karo
        if ch == 'R':
            ok = find(eb + 1) == s
        else:  # 'B' ya '.'  (normal pe dono node same component mein hain)
            ok = find(eb) == s
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