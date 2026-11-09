def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # n ==len of a
    # charges available
    max_charges = 2

    # time next charge is back
    next_recharge = 0

    # each one timestampp
    for t in A:

        # recharges are calc before the request
        while max_charges < 2 and next_recharge <= t:
            max_charges += 1

            if max_charges < 2:
                next_recharge += R

        if max_charges == 0:
            # / Nothing Left
            return "NO"

        if max_charges == 2:
            next_recharge = t + R

        max_charges -= 1

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