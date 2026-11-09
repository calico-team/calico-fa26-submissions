def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    charges = 2
    recharge_finish = -1

    for t in A:
        # Recharge any smoke charges that complete at or before the current timestamp t
        while charges < 2 and recharge_finish <= t:
            charges += 1
            if charges < 2:
                recharge_finish += R
            else:
                recharge_finish = -1

        # If no charge is available at timestamp t, request fails
        if charges == 0:
            return "NO"

        # Consume one smoke charge
        charges -= 1
        if charges == 1:
            recharge_finish = t + R

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