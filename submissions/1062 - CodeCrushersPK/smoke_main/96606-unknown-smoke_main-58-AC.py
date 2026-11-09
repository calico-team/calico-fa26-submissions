def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    wapsi_ka_time = []
    for right_now in A:
        wapsi_ka_time = [w for w in wapsi_ka_time if w > right_now]
        if len(wapsi_ka_time) == 2:
            return "NO"
        if len(wapsi_ka_time) == 0:
            wapsi_ka_time.append(right_now + R)
        else:
            wapsi_ka_time.append(wapsi_ka_time[-1] + R)
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
