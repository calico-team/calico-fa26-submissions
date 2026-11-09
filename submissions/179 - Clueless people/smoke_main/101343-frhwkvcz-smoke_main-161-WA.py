def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE
    s = ""
    for i in range(len(A)-1):
        x = A[i+1] - A[i]
        if x == R or x>=R:
            s+= "T"
        else:
            s+="F"

    if "F" in s:
        return "NO"
    else:
        return"YES"

    return ""


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
