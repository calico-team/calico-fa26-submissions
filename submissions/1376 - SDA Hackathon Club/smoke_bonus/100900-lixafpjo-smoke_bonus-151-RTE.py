def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE
    #pls let me get it right
    charges = 2
    nextRecharge = 0
    charging = False
    for i in range(N):
        time = A[i]
        while charges<2 and charging and nextRecharge<=time:
            charges+=1
            if charges<2:
                nextRecharge+=R
            else:
                charging = False
        if charges == 0:
            return "NO"
        if charges == 2:
            nextRecharge = time+r
            charging = True
        charges-=1
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
