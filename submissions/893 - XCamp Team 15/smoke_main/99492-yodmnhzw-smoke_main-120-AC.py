def solve(amount, time, listoftime):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE
    readytimes=[0,0,]
    for i in listoftime:
        if readytimes[0]>i:
            return "NO"
        new=max(i, readytimes[1])+time
        readytimes=sorted([readytimes[1],new])
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
