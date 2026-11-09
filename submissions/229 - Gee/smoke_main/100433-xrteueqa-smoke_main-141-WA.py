def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE
    available_smokes = 2
    time = A[0]
    for i in range(N):
        if A[i] - time < R:
            available_smokes -= 1
        time = A[i]
        
        if available_smokes < 0:
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
