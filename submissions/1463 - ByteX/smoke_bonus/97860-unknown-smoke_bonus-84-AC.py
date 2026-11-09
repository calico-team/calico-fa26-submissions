def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    charges = 2        ## charges Omen has right now
    next_ready = 0     ## time the next charge comes back (only matters if charges < 2)

    for t in A:
        ## Recharges happen before requests, so use <=.
        ## Charges recharge one at a time, so each restored charge
        ## starts the timer for the next one.
        while charges < 2 and next_ready <= t:
            charges += 1
            next_ready += R

        if charges == 0:
            return "NO"

        ## Using a charge from full starts the recharge timer
        if charges == 2:
            next_ready = t + R
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
