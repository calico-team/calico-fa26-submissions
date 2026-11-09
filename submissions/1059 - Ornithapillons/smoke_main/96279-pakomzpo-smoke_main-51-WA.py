def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    currentSmokeBuffer = 2

    lastSmokeRemoved = 0
    lastSmokeAdded = 0

    for i in range(N):
        while currentSmokeBuffer <= 2 and A[i] - lastSmokeAdded >= R:
            if currentSmokeBuffer == 0 and A[i] - 2*R > A[i - 1]:
                currentSmokeBuffer += 2
                lastSmokeAdded = A[i - 1] + 2*R
            else:
                currentSmokeBuffer += 1
                lastSmokeAdded = A[i - 1] + R

        if currentSmokeBuffer > 0:
            currentSmokeBuffer -= 1
        else:
            return "NO"

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
