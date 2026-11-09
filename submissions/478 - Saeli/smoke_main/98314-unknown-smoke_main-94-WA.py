
def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    charge = 2
    index = 0
    recharge_timer=0
    for time in range(0,max(A)+1):
        if time == (recharge_timer+R):
            if charge<2:
                charge+=1
            elif charge<3:
                if time == A[index]:
                    charge+=1
        if time == A[index]:
            charge -=1
            if charge <0:
                return "NO"
            recharge_timer=A[index]
            index+=1
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
