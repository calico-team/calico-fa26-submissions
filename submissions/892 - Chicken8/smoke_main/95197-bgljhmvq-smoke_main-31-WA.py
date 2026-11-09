def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    Time = 0
    Smokes = 2
    for i in range(0, N, 1):
        if i == 0:
            Time += A[i]
        else:
            Time += A[i] - A[i - 1]
        # print(Time)
        while Time >= R:
            if Time >= R:
                Time -= R
                Smokes += 1
            # print(Time)
        Smokes -= 1
        if Smokes < 0:
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
