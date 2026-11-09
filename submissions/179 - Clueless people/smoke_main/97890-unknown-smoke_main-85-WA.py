def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    #20 30 40 50 60

    # YOUR CODE HERE
    lives=2
    time=0
    for i in range(N):
        time+= R
        if lives>0:
            lives-=1 
        if time<A[i]:
            lives +=1
        elif lives==0 and time>A[i]:
            return "NO"
    return "YES"
        
        
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
