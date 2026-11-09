def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE
    smoke=2
    time_recharge=None
    for currenttime in A:
        while time_recharge is not None and time_recharge<=currenttime:
            smoke+=1
            if smoke==2:
                time_recharge=None
            else:
                time_recharge+=R
        if smoke==0:
            return "No"
        smoke-=1
        if time_recharge is None:
            time_recharge=currenttime+R

    return "Yes"


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
