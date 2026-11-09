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
        return (ch == 'B') == (mode == 0)

    comp = [-1] * (2 * N * M)
    cid = 0
    for r0 in range(N):
        for c0 in range(M):
            for m0 in (0, 1):
                s = (r0 * M + c0) * 2 + m0
                if comp[s] != -1 or not active(r0, c0, m0):
                    continue
                comp[s] = cid
                stack = [s]
                while stack:
                    v = stack.pop()
                    mode = v & 1
                    cell = v >> 1
                    r, c = divmod(cell, M)
                    for dr, dc in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                        nr, nc = r + dr, c + dc
                        if 0 <= nr < N and 0 <= nc < M and active(nr, nc, mode):
                            u = (nr * M + nc) * 2 + mode
                            if comp[u] == -1:
                                comp[u] = cid
                                stack.append(u)
                    if G[r][c] == '.':
                        u = cell * 2 + (1 - mode)
                        if comp[u] == -1:
                            comp[u] = cid
                            stack.append(u)
                cid += 1

    ans = []
    for (sr, sc), (er, ec) in zip(start, end):
        target = comp[(sr * M + sc) * 2]  
        base = (er * M + ec) * 2
        if comp[base] == target or comp[base + 1] == target:
            ans.append("YES")
        else:
            ans.append("NO")
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