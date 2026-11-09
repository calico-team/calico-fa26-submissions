def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE
    charges = 2
    continuous = 0

    for i in range(len(A)):
        if charges > 0:
            charges -= 1
            if (i + 1) < len(A):
                continuous += A[i + 1] - A[i]
                if continuous >= (R * 2):
                    charges = 2
                elif continuous >= R:
                    charges += 1
                if charges == 2:
                    continuous = 0
        else:
            return "NO"
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
