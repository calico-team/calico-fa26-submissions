def solve(N, R, A):

    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    t1, t2 = 0, 0
    for time in A:
        if t1 > time:
            return "NO"
        t1, t2 = t2, max(t2, time) + R
    return "YES"


def tokens():
    while True:
        try:
            line = input()
        except EOFError:
            return
        for x in line.split():
            yield x


def main():
    it = tokens()
    T = int(next(it))
    for _ in range(T):
        N = int(next(it))
        R = int(next(it))
        A = [int(next(it)) for _ in range(N)]
        print(solve(N, R, A))


if __name__ == '__main__':
    main()