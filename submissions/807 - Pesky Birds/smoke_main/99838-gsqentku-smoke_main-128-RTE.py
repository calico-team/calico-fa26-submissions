



smokeCharge = 2

def smoke():
    global smokeCharge
    smokeCharge -= 1
def smokeRecharge():
    global smokeCharge
    smokeCharge += 1

def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    #AList = A.split(" ")
    global smokeCharge
    if N > len(A):
        output = "NO"
        return output
    for lcv in range(1,100):
        if lcv%R == 0:
            smokeRecharge()
            if smokeCharge >= 2:
                smokeCharge = 2
        
        for lcv1 in A:
            if lcv == lcv1:
                if smokeCharge > 1:
                    smoke()
                    output = "YES"
                else:
                    output = "NO"
                    return output
    return output


# Starts round with 2 smoke charges - the max
# Using a smoke consumes one charge
# Once using a smoke, it will take R seconds to recharge
# Recharged sequencially; second only starts after first fully charged
# 

# while loop, checks if it is time, otherwise js continue recharging, and keeps adding to A

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



