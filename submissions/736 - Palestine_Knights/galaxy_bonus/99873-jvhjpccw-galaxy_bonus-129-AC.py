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

    def find(x):
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x

    def union(a, b):
        ra = find(a)
        rb = find(b)

        if ra == rb:
            return

        if size[ra] < size[rb]:
            ra, rb = rb, ra

        parent[rb] = ra
        size[ra] += size[rb]

    def active(tile, mode):
        return (
            tile == "."
            or (mode == 0 and tile == "B")
            or (mode == 1 and tile == "R")
        )

    for r in range(N):
        for c in range(M):
            tile = G[r][c]
            pos = r * M + c

            if tile == ".":
                union(pos, pos + total)

            if c + 1 < M:
                next_tile = G[r][c + 1]
                next_pos = pos + 1

                for mode in range(2):
                    if active(tile, mode) and active(next_tile, mode):
                        offset = mode * total
                        union(pos + offset, next_pos + offset)

            if r + 1 < N:
                next_tile = G[r + 1][c]
                next_pos = pos + M

                for mode in range(2):
                    if active(tile, mode) and active(next_tile, mode):
                        offset = mode * total
                        union(pos + offset, next_pos + offset)

    results = []

    for i in range(Q):
        sr, sc = start[i]
        er, ec = end[i]

        source = sr * M + sc
        target = er * M + ec

        source_root = find(source)

        target_blue = find(target)
        target_red = find(target + total)

        if source_root == target_blue or source_root == target_red:
            results.append("YES")
        else:
            results.append("NO")

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
