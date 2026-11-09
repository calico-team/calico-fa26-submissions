def find(parent, x):
    if parent[x] != x:
        parent[x] = find(parent, parent[x])
    return parent[x]


def union(parent, size, a, b):
    a = find(parent, a)
    b = find(parent, b)

    if a == b:
        return

    if size[a] < size[b]:
        a, b = b, a

    parent[b] = a
    size[a] += size[b]

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
    total = N * M
    parent = list(range(2 * total))
    size = [1] * (2 * total)

    for r in range(N):
        for c in range(M):
            cell = r * M + c
            tile = G[r][c]

            if tile == '.':
                union(parent, size, cell, cell + total)

            if r + 1 < N:
                nextCell = (r + 1) * M + c
                nextTile = G[r + 1][c]

                if tile != 'R' and nextTile != 'R':
                    union(parent, size, cell, nextCell)

                if tile != 'B' and nextTile != 'B':
                    union(parent, size, cell + total, nextCell + total)

            if c + 1 < M:
                nextCell = r * M + c + 1
                nextTile = G[r][c + 1]

                if tile != 'R' and nextTile != 'R':
                    union(parent, size, cell, nextCell)

                if tile != 'B' and nextTile != 'B':
                    union(parent, size, cell + total, nextCell + total)

    answers = []

    for (startRow, startCol), (endRow, endCol) in zip(start, end):
        startCell = startRow * M + startCol
        endCell = endRow * M + endCol

        if G[endRow][endCol] == 'R':
            endCell += total

        if find(parent, startCell) == find(parent, endCell):
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
