import sys
from collections import deque


def getResult(valueList, limit):
    valueList.sort()

    total = len(valueList) * limit
    activeValues = deque()
    lastKey = -1

    for groupKey, currentValue, currentType in valueList:
        if groupKey != lastKey:
            activeValues.clear()
            lastKey = groupKey

        while activeValues and currentValue - activeValues[0] >= limit:
            activeValues.popleft()

        if currentType == "E":
            activeValues.append(currentValue)
        else:
            total -= len(activeValues)

    return total


def solve():
    readLine = sys.stdin.readline
    caseCount = int(readLine())
    resultList = []

    for _ in range(caseCount):
        size, limit = map(int, readLine().split())
        valueList = []

        for _ in range(size):
            parts = readLine().split()
            x = int(parts[0])
            y = int(parts[1])
            valueList.append((x + y, x, parts[3]))

        resultList.append(str(getResult(valueList, limit)))

    sys.stdout.write("\n".join(resultList))


if __name__ == "__main__":
    solve()
