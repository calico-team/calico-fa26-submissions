from collections import deque

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
        if G[r][c] == ".":
            return True
        if mode == 0 and G[r][c] == "B":
            return True
        if mode == 1 and G[r][c] == "R":
            return True
        return False

    comp = [[[0] * M for _ in range(N)] for _ in range(2)]
    count = 0
    directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]

    for mode in range(2):
        for r in range(N):
            for c in range(M):
                if active(r, c, mode) and comp[mode][r][c] == 0:
                    count += 1
                    comp[mode][r][c] = count
                    queue = deque([(mode, r, c)])

                    while queue:
                        m, a, b = queue.popleft()

                        for dr, dc in directions:
                            na, nb = a + dr, b + dc
                            if 0 <= na < N and 0 <= nb < M:
                                if active(na, nb, m) and comp[m][na][nb] == 0:
                                    comp[m][na][nb] = count
                                    queue.append((m, na, nb))

                        if G[a][b] == ".":
                            other = 1 - m
                            if comp[other][a][b] == 0:
                                comp[other][a][b] = count
                                queue.append((other, a, b))

    answers = []
    for i in range(Q):
        rs, cs = start[i]
        re, ce = end[i]
        island = comp[0][rs][cs]
        if comp[0][re][ce] == island or comp[1][re][ce] == island:
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
