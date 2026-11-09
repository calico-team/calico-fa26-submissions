
from collections import deque


def solve(N, R, A):
    charges = 2
    waiting = deque()

    for now in A:

        while waiting and waiting[0] <= now:
            waiting.popleft()
            charges += 1

        if charges == 0:
            return "NO"

        charges -= 1

        if waiting:
            waiting.append(waiting[-1] + R)
        else:
            waiting.append(now + R)

    return "YES"


def main():
    T = int(input())

    for _ in range(T):
        temp = input().split()
        N = int(temp[0])
        R = int(temp[1])

        A = list(map(int, input().split()))

        print(solve(N, R, A))


if __name__ == '__main__':
    main()
