def solve(smokeReq, timeCharge, array):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    time = 0
    charges = 2

    for i in array:
        if charges < 2:
            recovered = (i - time) // timeCharge
            charges = min(2, charges + recovered)
            time += recovered * timeCharge

        if charges == 2:
            time = i

        if charges == 0:
            return "NO"

        charges -= 1


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
