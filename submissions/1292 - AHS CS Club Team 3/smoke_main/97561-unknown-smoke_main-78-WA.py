def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    """
    Sequentially go through each request, update smoke cooldowns, and check if request is doable, if so reset cooldown on the latest smoke, else return no
    """
    time = 0
    s1 = 0
    s2 = 0
    latest = 2
    for i in range(N):
        dif = A[i] - time
        if latest == 2:
            if s2 > 0 and dif > 0:
                s2 -= dif
                dif = 0
                if s2 < 0:
                    dif += abs(s2)
                    s2 = 0
            if s1 > 0 and dif > 0:
                s1 -= dif
                dif = 0
        elif latest == 1:
            if s1 > 0 and dif > 0:
                s1 -= dif
                dif = 0
                if s1 < 0:
                    dif += abs(s1)
                    s1 = 0
            if s2 > 0 and dif > 0:
                s2 -= dif
                dif = 0
        if s1 == 0:
            s1 = R
            latest = 1
        elif s2 == 0:
            s2 = R
            latest = 2
        else:
            return "NO"
        time = A[i]
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
