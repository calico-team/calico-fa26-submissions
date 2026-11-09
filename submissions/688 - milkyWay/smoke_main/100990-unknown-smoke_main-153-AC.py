def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    available_charges = 2 # smoke charges 

    # Time at which the next charge finishes recharging.
    # Only meaningful while available_charges < 2.
    next_recharge_time = 0

    for request_time in A:
        while available_charges < 2 and next_recharge_time <= request_time:
            available_charges += 1

            if available_charges < 2:
                next_recharge_time += R

        if available_charges == 0:
            return "NO"

        if available_charges == 2: # available_charges == 2 means we have 2 charges, so we can use the one and start rechrging
            next_recharge_time = request_time + R

        available_charges -= 1 # update available charges after using one

    return "YES" # if all requests were satisfied


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