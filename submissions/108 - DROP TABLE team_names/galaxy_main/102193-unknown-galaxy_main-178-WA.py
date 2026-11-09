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
    returned = []

    vertical_walls = []
    for col in range(M-1):
        
        wall = True
        for row in range(N):
            if [G[row][col], G[row][col+1]] != ["R", "B"] and [G[row][col], G[row][col+1]] != ["B", "R"]:
                wall = False
                break


        if wall:
            vertical_walls.append(col)

    horizontal_walls = []
    for row in range(N-1):
        wall = True

        for col in range(M):
            if [G[row][col], G[row+1][col]] != ["R", "B"] and [G[row][col], G[row+1][col]] != ["B", "R"]:
                wall = False
                break
        if wall:
            horizontal_walls.append(row)



    for i in range(Q):
        final_output = "YES"

        currStart = start[i]
        currEnd = end[i]

        farthestLeft = max((x for x in vertical_walls if x < currStart[1]), default=0)
        farthestRight = min((x for x in vertical_walls if x > currStart[1]), default=M-1)
        farthestUp = max((y for y in horizontal_walls if y < currStart[0]), default=0)
        farthestDown = min((y for y in horizontal_walls if y > currStart[0]), default=N-1)


        if currEnd[1] > farthestRight or currEnd[1] < farthestLeft:
            final_output = "NO"

        if currEnd[0] > farthestDown or currEnd[0] < farthestUp:
            final_output = "NO"


        returned.append(final_output)

    return returned

def getColumn(grid, colNum):
    col = []

    for row in grid:
        col.append(row[colNum])

    return col

def getRow(grid, rowNum):
    return grid[rowNum]

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
