def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    recharge_1 = 0
    recharge_2 = 0
    for i in A:
        if i < recharge_1 and i < recharge_2:
            return "NO"

        if i >= recharge_2:
            recharge_2 = i + R
        else:
            recharge_1 = recharge_2
            recharge_2 = recharge_2 + R

    return "YES"


def main():
    T = int(input())
    for _ in range(T):
        temp = input().split()
        N = int(temp[0])
        R = int(temp[1])
        A = list(map(int, input().split()))
        print(solve(N, R, A))


if __name__ == "__main__":
    main()
