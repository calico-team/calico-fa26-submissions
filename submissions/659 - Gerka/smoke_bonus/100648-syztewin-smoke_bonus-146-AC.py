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
    for time in A:
        if time >= currentCooldown:
            if not charge1:
                charge1 = True
                if not charge2:
                    currentCooldown = currentCooldown + R
                    if time >= currentCooldown:
                        charge2 = True
                        currentCooldown = 0
                else:
                    currentCooldown = 0
            elif not charge2:
                charge2 = True
                currentCooldown = 0
                
        if charge2:
            charge2 = False
            if currentCooldown == 0:
                currentCooldown = time + R
        elif charge1:
            charge1 = False
            if currentCooldown == 0:
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
