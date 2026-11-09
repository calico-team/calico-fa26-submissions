import math

def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    charges = 2

    for i in range(N):
        
        t = A[i]
        if i > 0:
            t = A[i] - A[i-1]
        charges += math.floor(t / R)
        charges -= 1

        if charges < 0:
            return "NO"

        charges = min (charges, 2)

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


