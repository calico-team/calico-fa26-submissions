def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    a = None
    b = 2
    for x in A:
        while a != None and x >= a:
            b += 1
            if b == 2:
                a = None
            else:
                a += R
        if b == 0:
            return "NO"
        b -= 1
        if a == None:
            a = x + R
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
