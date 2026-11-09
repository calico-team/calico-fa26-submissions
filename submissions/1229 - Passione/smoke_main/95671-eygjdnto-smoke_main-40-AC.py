def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE
    when_back = []

    for i in A:
        while len(when_back) > 0 and when_back[0] <= i:
            when_back.pop(0)

        if len(when_back) == 2:
            return "NO"

        if len(when_back) == 0:
            when_back.append(i + R)
        else:
            when_back.append(when_back[0] + R)
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
