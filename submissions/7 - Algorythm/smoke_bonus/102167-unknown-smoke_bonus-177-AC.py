def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    from collections import deque

    charges = 2          # charges currently available
    recharging = deque() # completion times of charges being recharged (in order)

    for a in A:
        # Restore any charges whose recharge finished by time a
        while recharging and recharging[0] <= a:
            recharging.popleft()
            charges += 1

        if charges == 0:
            return "NO"

        charges -= 1
        # Recharge starts now, or when the previous recharge finishes (sequential)
        start = max(a, recharging[-1]) if recharging else a
        recharging.append(start + R)

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