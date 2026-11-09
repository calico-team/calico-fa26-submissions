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
    # YOUR CODE HERE

    total = N * M
    flat = "".join(G)

    def chk_active(cell, mode):
        ch = flat[cell]
        return ch == '.' or (ch == 'B' and mode == 0) or (ch == 'R' and mode == 1)


    comp = [-1] * (2 * total)
    label = 0

    for first in range(2 * total):
        if comp[first] != -1 or not chk_active(first >> 1, first & 1):
            continue

        comp[first] = label
        stack = [first]
        while stack:
            state = stack.pop()
            cell = state >> 1
            mode = state & 1
            r, c = divmod(cell, M)

            if r > 0:
                nb = cell - M
                if comp[nb * 2 + mode] == -1 and chk_active(nb, mode):
                    comp[nb * 2 + mode] = label
                    stack.append(nb * 2 + mode)
            if r < N - 1:
                nb = cell + M
                if comp[nb * 2 + mode] == -1 and chk_active(nb, mode):
                    comp[nb * 2 + mode] = label
                    stack.append(nb * 2 + mode)
            if c > 0:
                nb = cell - 1
                if comp[nb * 2 + mode] == -1 and chk_active(nb, mode):
                    comp[nb * 2 + mode] = label
                    stack.append(nb * 2 + mode)
            if c < M - 1:
                nb = cell + 1
                if comp[nb * 2 + mode] == -1 and chk_active(nb, mode):
                    comp[nb * 2 + mode] = label
                    stack.append(nb * 2 + mode)

            if flat[cell] == '.':
                other = state ^ 1
                if comp[other] == -1:
                    comp[other] = label
                    stack.append(other)

        label += 1

    answers = []
    for i in range(Q):
        sr, sc = start[i]
        er, ec = end[i]
        s_state = (sr * M + sc) * 2          
        e_cell = er * M + ec
        ch = flat[e_cell]
        
        e_state = e_cell * 2 + (1 if ch == 'R' else 0)

        if comp[s_state] == comp[e_state] and comp[s_state] != -1:
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
