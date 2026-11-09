def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """


    R = 0
    R2 = 0
    for i in range(len(A)):
        if R != 0:
            if A[i+1]-A[i] > R2:
                R2 = 0
                R = A[i+1]-A[i] - R2
                if R < 0:
                    R = 0 
            else: R2 = R2 - (A[i+1]-A[i])
        if R == 0:
            R = 10
            print("YES")
        elif R2 == 0:
            R2 = 10
            print("YES")
        else:
            print("NO")




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
