def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    charge1 = True
    charge2 = True
    currentCooldown = 0
    for time in range(A[-1]+1):
        if time == currentCooldown:
            if not charge1:
                charge1 = True
                if not charge2:
                    currentCooldown = time + R
            elif not charge2:
                charge2 = True
                
        if time in A:
            if charge2:
                charge2 = False
                currentCooldown = time + R
            elif charge1:
                charge1 = False
                currentCooldown = time + R
            else:
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
