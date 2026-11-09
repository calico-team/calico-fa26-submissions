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
    group = [[-1] * (N * M) for _ in range(2)]

    def is_open(r, c, mode):
        ch = G[r][c]
        if ch == '.':
            return True
        if ch == 'B':
            return mode == 0
        return mode == 1

    count = 0
    for mode in range(2):
        for r in range(N):
            for c in range(M):
                spot = r * M + c
                if group[mode][spot] != -1 or not is_open(r, c, mode):
                    continue
                group[mode][spot] = count
                stack = [(r, c, mode)]
                while stack:
                    x, y, m = stack.pop()
                    for nx, ny in ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)):
                        if 0 <= nx < N and 0 <= ny < M:
                            nspot = nx * M + ny
                            if group[m][nspot] == -1 and is_open(nx, ny, m):
                                group[m][nspot] = count
                                stack.append((nx, ny, m))
                    if G[x][y] == '.':
                        other = 1 - m
                        if group[other][x * M + y] == -1:
                            group[other][x * M + y] = count
                            stack.append((x, y, other))
                count += 1

    answers = []
    for i in range(Q):
        sr, sc = start[i]
        er, ec = end[i]
        home = group[0][sr * M + sc]
        goal = er * M + ec
        if home == group[0][goal] or home == group[1][goal]:
            answers.append("YES")
        else:
            answers.append("NO")
    return answers


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