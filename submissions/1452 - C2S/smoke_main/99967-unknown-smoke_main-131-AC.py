def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    charges = 2        
    ready_at = None     

    for t in A:

        while charges < 2 and ready_at <= t:
            charges += 1
            if charges < 2:
                ready_at += R
            else:
                ready_at = None    # dono full

        if charges == 0:
            return "NO"

        charges -= 1
        if ready_at is None:
            ready_at = t + R

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