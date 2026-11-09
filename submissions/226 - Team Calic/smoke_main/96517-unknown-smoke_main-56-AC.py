def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    charges=2
    pending=0
    next_recharge=0
    for t in A:
        #Recharge charges that are pending
        while next_recharge<=t and pending>0:
            charges+=1
            pending-=1
            next_recharge+=R
        #Check If we have a charge, use it
        if charges==0:
            return "NO"
        charges-=1
        #Schedule a recharge for the used charge
        if pending==0:
            next_recharge=t+R
        pending+=1
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
