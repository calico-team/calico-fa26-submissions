def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    cursmoke=1
    for i in range(1, N):
        if cursmoke==2:
            cursmoke-=1
        elif cursmoke==1:
            if A[i]-A[i-1]<R:
                cursmoke-=1
        else:
            if A[i]-A[i-1]>=2*R:
                cursmoke+=1
            elif A[i]-A[i-1]<R:
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
