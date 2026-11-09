def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    charges = 2
    recharge_time = []

    for time in A:
        while recharge_time and recharge_time[0] <= time:
            recharge_time.pop(0)
            charges += 1
        if charges == 0:
            return "NO"
        charges -= 1

        if len(recharge_time) == 0:
            recharge_time.append(time+R)
        else:
            recharge_time.append(recharge_time[-1]+R)

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
