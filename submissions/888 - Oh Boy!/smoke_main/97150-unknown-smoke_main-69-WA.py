def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE
    charge = 2
    cd = False
    for i in range(N-1):
        charge -= 1
        if (i-1 >= 0 and A[i+1] - A[i-1] >= R and cd == False):
            charge += 1
            cd = True
        elif A[i+1] - A[i] >= R:
            charge += 1
            cd = False
        if charge == 0:
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