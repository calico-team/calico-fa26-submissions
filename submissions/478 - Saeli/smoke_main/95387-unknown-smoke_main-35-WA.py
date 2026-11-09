
def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    recharge_timer=A[0]
    charge=1
    for i in range(1,N):
        if(A[i]-recharge_timer>=R):
            if charge<3:
                charge+=1
                recharge_timer=recharge_timer+R

        charge-=1
        if charge<0:
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
