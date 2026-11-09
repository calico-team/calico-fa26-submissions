# Source: https://usaco.guide/general/io
def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE
    count = 0
    recharged = 0
    for time in A:
        while time >= recharged and count != 0:
            count -= 1
            recharged += R
        if count == 0:
            recharged = time + R 
        count += 1
        if count > 2:
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