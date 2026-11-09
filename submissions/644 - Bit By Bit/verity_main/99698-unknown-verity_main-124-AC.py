import sys


def solve():
    readLine = sys.stdin.readline
    caseCount = int(readLine())

    for _ in range(caseCount):
        size, typeCount = map(int, readLine().split())
        charList = readLine().split()
        pattern = "_" * size

        for currentChar in charList:
            guess = pattern.replace("_", currentChar)
            print(guess, flush=True)

            reply = readLine().strip()

            if not reply:
                return

            if reply == "CORRECT":
                break

            pattern = reply


if __name__ == "__main__":
    solve()
