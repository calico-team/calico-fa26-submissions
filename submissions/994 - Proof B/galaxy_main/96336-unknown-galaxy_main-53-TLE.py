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
    seen = []
    search = [(end[0][0], end[0][1], G[end[0][0]][end[0][1]])]
    while search:
        t = search.pop()
        if t in seen:
            continue

        # print(f"searching: {t}")

        news = []

        # test neighbors
        if t[0] > 0:
            news.append((t[0] - 1, t[1], G[t[0] - 1][t[1]]))
        if t[0] < N - 1:
            news.append((t[0] + 1, t[1], G[t[0] + 1][t[1]]))
        if t[1] > 0:
            news.append((t[0], t[1] - 1, G[t[0]][t[1] - 1]))
        if t[1] < M - 1:
            news.append((t[0], t[1] +  1, G[t[0]][t[1] + 1]))

        # print(f"possible: {news}")

        for n in news:
            if n[2] == t[2] or n[2] == "." or t[2] == ".":
                search.append(n)
                # print(f"new: {n}")

        seen.append(t)

    # print(seen)

    sols = []
    for coord in start:
        if (coord[0], coord[1], G[coord[0]][coord[1]]) in seen:
            sols.append("YES")
        else:
            sols.append("NO")
    return sols

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
