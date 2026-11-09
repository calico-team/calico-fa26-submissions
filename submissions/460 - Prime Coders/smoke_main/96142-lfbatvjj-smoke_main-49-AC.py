
def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """

    available = 2
    recharge = []

    for time in A:

        # Process completed recharges
        while recharge and recharge[0] <= time:
            recharge.pop(0)
            available += 1

        # Check whether a smoke charge is available
        if available == 0:
            return "NO"

        # Use one smoke charge
        available -= 1

        # Schedule its recharge
        if recharge:
            next_time = recharge[-1] + R
        else:
            next_time = time + R

        recharge.append(next_time)

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
