def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE
    for num1, num2 in zip(A, A[1:]):
        diff = num2-num1
        if num2 == A[-1]:
            if diff >= R:
                return "YES"
            else:
                return "NO"
        else:
            if diff >= R:
                continue
            else:
                return "NO"


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
