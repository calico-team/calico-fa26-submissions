import sys


def amnesiac():
    phase = read_your_input().strip()
    size = int(read_your_input())

    if phase == b"FIRST":
        nextList = [[] for _ in range(size + 1)]

        for _ in range(size - 1):
            firstValue, secondValue = map(int, read_your_input().split())
            nextList[firstValue].append(secondValue)
            nextList[secondValue].append(firstValue)

        parentList = [0] * (size + 1)
        pending = [1]

        while pending:
            currentValue = pending.pop()

            for nextValue in nextList[currentValue]:
                if nextValue == parentList[currentValue]:
                    continue

                parentList[nextValue] = currentValue
                pending.append(nextValue)

        valueList = parentList[2:]
        checkValue = 0

        for currentValue in valueList:
            checkValue ^= currentValue

        valueList.append(checkValue)
        sys.stdout.write(" ".join(map(str, valueList)) + "\n")

    else:
        valueList = list(map(int, read_your_input().split()))
        missingIndex = -1
        checkValue = 0

        for index, currentValue in enumerate(valueList):
            if currentValue == -1:
                missingIndex = index
            else:
                checkValue ^= currentValue

        valueList[missingIndex] = checkValue

        resultList = [
            f"{index + 2} {valueList[index]}"
            for index in range(size - 1)
        ]
        sys.stdout.write("\n".join(resultList) + "\n")


def read_your_input():
    return sys.stdin.buffer.readline()


if __name__ == "__main__":
    amnesiac()
