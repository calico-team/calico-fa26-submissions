import sys
from collections import deque


def getResult(values, limit, capacity):
    size = len(values)
    nextList = [[] for _ in range(size)]
    countList = [0] * (size + 1)
    pending = deque()
    for index, value in enumerate(values):
        if value == 0:
            pending.append((index, 1))
        else:
            nextList[value - 1].append(index)
    while pending:
        currentValue, currentDepth = pending.popleft()
        countList[currentDepth] += 1

        for nextValue in nextList[currentValue]:
            pending.append((nextValue, currentDepth + 1))

    result = min(size, limit * capacity)
    total = 0
    for currentDepth in range(1, min(size, limit) + 1):
        total += countList[currentDepth]
        result = min(
            result,
            total + (limit - currentDepth) * capacity
        )
    return result


def solve():
    readLine = sys.stdin.readline
    caseCount = int(readLine())
    for _ in range(caseCount):
        size, limit, capacity = map(int, readLine().split())
        values = list(map(int, readLine().split()))
        print(getResult(values, limit, capacity))


if __name__ == "__main__":
    solve()
