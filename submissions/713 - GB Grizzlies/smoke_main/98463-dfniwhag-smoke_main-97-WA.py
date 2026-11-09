def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE
    smokes = 2
    counter = 0
    for i, t in enumerate(A):
        if i > 0:
            dt = t - A[i - 1]
            counter += dt
        if i > 0 and counter >= R and smokes < 2:
            smokes += 1
            counter = 0
        if smokes == 0:
            return "NO"
        smokes -= 1
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
