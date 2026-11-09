def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE
    noOfBalls = 1
    prev = A[0]
    for a in A[1:]:
        if a - prev >= R:
            if noOfBalls < 2:
                noOfBalls += 1
                prev = a
        
        if noOfBalls > 0:
            noOfBalls -= 1
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
