def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    charges = 2
    nxt = 0 
    for t in A:

        while charges < 2 and t >= nxt:
            charges += 1
            nxt += R        
        if charges == 0:
            return "NO"
        if charges == 2:
            nxt = t + R       
        charges -= 1
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
