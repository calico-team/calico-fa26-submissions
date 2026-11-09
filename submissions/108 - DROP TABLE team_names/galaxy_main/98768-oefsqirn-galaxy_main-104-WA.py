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
    # REPEAT all for horizontal walls
    returned = []

    # llooking for RB walls
    rb_walls_vertical = []
    
    allR = ["R"] * N
    allB = ["B"] * N

    for i in range(M-1):
        if getColumn(G, i) == allR:
            if getColumn(G, i+1) == allB:
                rb_walls_vertical.append(i)
                rb_walls_vertical.append(i+1)

    # BR walls
    br_walls_vertical = []
    for i in range(M-1):
        if getColumn(G, i) == allB:
            if getColumn(G, i+1) == allR:
                br_walls_vertical.append(i)
                br_walls_vertical.append(i+1)

    merged_walls_vertical = list(set(rb_walls_vertical + br_walls_vertical))


    # Horizontal time

    # llooking for RB walls
    rb_walls_horizontal = []
    
    allR = "R" * M
    allB = "B" * M

    for i in range(N-1):
        if getRow(G, i) == allR:
            if getRow(G, i+1) == allB:
                rb_walls_horizontal.append(i)
                rb_walls_horizontal.append(i+1)

    # BR walls
    br_walls_horizontal = []
    for i in range(N-1):
        if getRow(G, i) == allB:
            if getRow(G, i+1) == allR:
                br_walls_horizontal.append(i)
                br_walls_horizontal.append(i+1)

    merged_walls_horizontal = list(set(rb_walls_horizontal + br_walls_horizontal))


    for i in range(Q):
        final_output = "YES"

        currStart = start[i]
        currEnd = end[i]

        farthestLeft = max((x for x in merged_walls_vertical if x < currStart[1]), default=0)
        farthestRight = min((x for x in merged_walls_vertical if x > currStart[1]), default=M-1)
        farthestUp = max((y for y in merged_walls_horizontal if y < currStart[0]), default=0)
        farthestDown = min((y for y in merged_walls_horizontal if y > currStart[0]), default=N-1)


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



# For it to fail
# it needs to be on the FAR end of an RB wall