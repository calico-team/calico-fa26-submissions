
from collections import deque

def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """

    available = 2
    recharge = deque()
    possible = True

    for t in A:
        # Recharge all charges ready at time t
        while recharge and recharge[0] <= t:
            recharge.popleft()
            available += 1

        if available == 0:
            possible = False
            break

        # Consume one charge
        available -= 1

        # Schedule its recharge
        if recharge:
            recharge.append(recharge[-1] + R)
        else:
            recharge.append(t + R)

    return "YES" if possible else "NO"


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
