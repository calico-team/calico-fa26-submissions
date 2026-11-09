def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    rech=2
    nr=0
    for i in range(N):
        rech=rech-1
        if nr != 0 and nr <= A[i]:
            rech=rech+1
        if rech<2:
            nr = A[i]+R
        if rech <1 and A[i]<nr:
            return "NO"

    # YOUR CODE HERE
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
