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
    for i in range(N):
        dif = A[i] - time
        if s1 > 0:
            s1 -= dif
            dif = 0
            if s1 < 0:
                dif += abs(s1)
                s1 = 0
        if s2 > 0 and dif > 0:
            s2 -= dif
            dif = 0
        if s2 == 0:
            s2 = R
        elif s1 == 0:
            s1 = R
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
