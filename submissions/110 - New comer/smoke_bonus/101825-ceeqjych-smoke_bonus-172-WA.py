def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE
    count = 2
    recharge = -1
    
    for t in A:

        if recharge != -1 and t >= recharge:
            count += 1
            recharge += R

            if count == 2:
                recharge = -1

        if count == 0:
            return "NO"

        count -= 1

        if recharge == -1 and count < 2:
            recharge = t + R

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
