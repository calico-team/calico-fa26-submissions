def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE
    smokes = 2
    reloadTimeLeft = None
    reloading = False
    for time1 in A:
        while reloadTimeLeft is not None and reloadTimeLeft<=time1 and smokes<2:
            smokes += 1
            if smokes<2:
                reloadTimeLeft += R
            else:
                reloadTimeLeft = None
        if smokes==0:
            return "No"
        smokes -= 1
        if smokes <2 and nextReload is None:
            nextReload = time1 + R
        
        
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
