def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE
    r1 = 0
    r2 = 0
    for t in A:
        if r1 > t:
            return "NO"
        nr = r2
        if t > nr:
            nr = t
        nr += R
        r1 = r2
        r2 = nr
        if r1 > r2:
            r1, r2 = r2, r1
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
