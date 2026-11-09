def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE
    t1=0
    t2=0
    
    for i in A:
        if t1>i and t2>i:
            return 'NO'
        if t1<=t2:
            t1=max(i,t2)+R
        else:
            t2=max(i,t1)+R
    
    
    return "yes"


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
