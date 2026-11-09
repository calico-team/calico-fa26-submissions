import sys


def checkCase(values, interval):
    count = 2
    nextTime = 0

    for currentTime in values:
        while count < 2 and nextTime <= currentTime:
            count += 1
            nextTime += interval

        if count == 0:
            return False

        if count == 2:
            nextTime = currentTime + interval

        count -= 1

    return True


def solve():
    readLine = sys.stdin.buffer.readline
    caseCount = int(readLine())
    resultList = []

    for _ in range(caseCount):
        size, interval = map(int, readLine().split())
        values = map(int, readLine().split())

        result = "YES" if checkCase(values, interval) else "NO"
        resultList.append(result)

    sys.stdout.write("\n".join(resultList))


if __name__ == "__main__":
    solve()
