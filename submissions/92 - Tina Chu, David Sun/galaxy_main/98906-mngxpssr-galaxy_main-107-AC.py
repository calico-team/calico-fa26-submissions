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
    parent = list(range(N*M))
    result = []

    # find connected tile(s)
    def find(x):
        while (parent[x]!=x):
            parent[x]=parent[parent[x]]
            x=parent[x]

        return x

    # combine connected tile(s) together
    def union(a, b):
        rootA, rootB = find(a), find(b)
        if rootA != rootB:
            parent[rootA] = rootB

    def verify(firstTile, secondTile): # can these 2 connect
        return not((firstTile=='R' and secondTile=='B') or 
                   (firstTile=='B' and secondTile=='R'))

    for i in range(N):
        for j in range(M):
            current = G[i][j]

            # check right-neighboring tile(s)
            if j + 1 < M and verify(current, G[i][j + 1]):
                union(i * M + j, i * M + j + 1)

            # check down-neighboring tile(s)
            if i + 1 < N and verify(current, G[i + 1][j]):
                union(i * M + j, (i + 1) * M + j)

    for i in range(Q):
        rowStart = start[i][0]
        colStart = start[i][1]

        rowEnd = end[i][0]
        colEnd = end[i][1]

        # check if start and end are of the same connection
        if find(rowStart * M + colStart) == find(rowEnd * M + colEnd):
            result.append("YES")
        else:
            result.append("NO")

    return result

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
