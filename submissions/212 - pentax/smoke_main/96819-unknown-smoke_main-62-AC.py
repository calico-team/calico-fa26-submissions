def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    charges = 2
    recharges = []
    idx = 0
    for t in A:
        while idx < len(recharges) and recharges[idx] <= t:
            charges += 1
            idx += 1
        if charges > 0:
            charges -= 1
            if idx == len(recharges):
                recharges.append(t + R)
            else:
                recharges.append(recharges[-1] + R)
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
