def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    currentSmokeBuffer = 2

    lastSmokeAdded = 0

    for i in range(N):
        if currentSmokeBuffer <= 2:
            if A[i] - lastSmokeAdded >= 2*R:
                if currentSmokeBuffer <= 1:
                    lastSmokeAdded = A[i-1] + 2*R
                    currentSmokeBuffer += 1
                else:
                    lastSmokeAdded = A[i-1] + R
                    currentSmokeBuffer += 1

            if A[i] - lastSmokeAdded >= R:
                lastSmokeAdded = A[i-1] + R
                currentSmokeBuffer += 1

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
