def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    charges = 1
    timepassed = A[0]
    old = timepassed//R
    for i in range(1,N):
        timepassed = A[i]
        if timepassed//R > old:
            charges += (timepassed//R-old)
            if charges > 2:
                charges = 2
            old = timepassed//R
        charges -= 1
        if charges < 0:
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
