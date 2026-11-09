def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE
    present = 2
    remaining = 0
    nextRecharge = 0

    for t in A:

        while remaining > 0 and nextRecharge <= t:
            remaining -= 1
            present += 1

            if remaining > 0:
                nextRecharge += R

        if present == 0:
            return "NO"

        present -= 1

        if remaining == 0:
            nextRecharge = t + R

        remaining += 1

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
