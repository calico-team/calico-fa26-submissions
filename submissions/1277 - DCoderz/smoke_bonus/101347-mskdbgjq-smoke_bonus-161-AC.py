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
        while rech < 2 and nr <= A[i]:
            rech += 1
            nr = nr+R
        if rech <1:
            return "NO"
        rech=rech-1
        if rech == 1:
            nr = A[i] + R

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
