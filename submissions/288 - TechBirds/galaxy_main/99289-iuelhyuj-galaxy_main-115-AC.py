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
    leader =list(range(N * M * 2))

    def find(v):

        while leader[v] != v:

            leader[v] = leader[leader[v]]

            v = leader[v]
        return v

    def union(a,b):

        ra, rb = find(a), find(b)

        if ra != rb:

            leader[ra] = rb

    def active(ch, mode):

        return ch == '.' or(ch == 'B' and mode == 0) or(ch == 'R' and mode == 1)

    for r in range(N):
        line=G[r]

        for c in range(M):
            ch = line[c]

            spot = r * M + c

            if ch == '.':
                union(spot * 2, spot * 2 + 1)

            for phase in (0,1):
                if not active(ch,phase):

                    continue

                if c + 1 < M and active(line[c + 1],phase):
                    union(spot * 2 + phase, (spot + 1) * 2 + phase)

                if r + 1 < N and active(G[r + 1][c],phase):

                    union(spot * 2 + phase, (spot + M) * 2 + phase)

    results = []

    for (sr, sc), (er, ec) in zip(start,end):

        s_state = (sr * M + sc) * 2

        e_cell = er * M + ec

        e_mode = 1 if G[er][ec] == 'R' else 0

        linked = find(s_state) == find(e_cell * 2 + e_mode)

        results.append("YES" if linked else "NO")

    return results   
    

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
