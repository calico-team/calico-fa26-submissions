def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.
    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    c = 2
    nxt = 0
    for x in A:
        while c < 2 and x >= nxt:
            c += 1
            nxt += R
        if c == 0:
            return "NO"
        if c == 2:
            nxt = x + R
        c -= 1
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
