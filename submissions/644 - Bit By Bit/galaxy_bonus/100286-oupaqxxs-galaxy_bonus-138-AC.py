import sys


def getGroups(grid):
    rowCount = len(grid)
    colCount = len(grid[0])
    groups = [[-1] * colCount for _ in range(rowCount)]
    moves = [(1, 0), (-1, 0), (0, 1), (0, -1)]
    groupId = 0
    for row in range(rowCount):
        for col in range(colCount):
            if groups[row][col] != -1:
                continue
            groups[row][col] = groupId
            stack = [(row, col)]
            while stack:
                currentRow, currentCol = stack.pop()
                currentValue = grid[currentRow][currentCol]
                for rowStep, colStep in moves:
                    nextRow = currentRow + rowStep
                    nextCol = currentCol + colStep

                    if not (
                        0 <= nextRow < rowCount
                        and 0 <= nextCol < colCount
                    ):
                        continue

                    if groups[nextRow][nextCol] != -1:
                        continue

                    nextValue = grid[nextRow][nextCol]

                    if (
                        currentValue == "."
                        or nextValue == "."
                        or currentValue == nextValue
                    ):
                        groups[nextRow][nextCol] = groupId
                        stack.append((nextRow, nextCol))
            groupId += 1
    return groups


def solve():
    readLine = sys.stdin.readline
    writeLine = sys.stdout.write
    caseCount = int(readLine())

    for _ in range(caseCount):
        rowCount, colCount, queryCount = map(int, readLine().split())
        grid = [readLine().strip() for _ in range(rowCount)]
        groups = getGroups(grid)

        for _ in range(queryCount):
            firstRow, firstCol, secondRow, secondCol = map(
                int, readLine().split()
            )

            if groups[firstRow][firstCol] == groups[secondRow][secondCol]:
                writeLine("YES\n")
            else:
                writeLine("NO\n")


if __name__ == "__main__":
    solve()
