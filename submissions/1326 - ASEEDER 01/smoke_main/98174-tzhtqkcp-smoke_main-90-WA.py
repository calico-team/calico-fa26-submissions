def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    smoke = A[1]
    result = True
    for i in range(2,len(A)):
        if A[i] - smoke < R:
            result = False
            break
        else:
            smoke = A[i]
    if result == True:
        return "Yes"
    else:
        return "No"
    


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
