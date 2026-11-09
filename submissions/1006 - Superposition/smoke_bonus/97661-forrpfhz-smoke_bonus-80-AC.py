def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    charges_count = 2
    next_recharge = 0

    for a_t in A:
        while charges_count < 2 and a_t >= next_recharge:
            charges_count += 1
            next_recharge += R

        if charges_count == 0:
            return "NO"

        if charges_count == 2:
            next_recharge = a_t + R
        charges_count -= 1

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
