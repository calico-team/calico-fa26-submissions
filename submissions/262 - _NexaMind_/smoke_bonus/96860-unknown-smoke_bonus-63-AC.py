def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    t1 = 0
    t2 = 0

    for a in A:
        available1= t1 <= a
        available2= t2 <= a
        if not available1 and not available2:
            return "NO"
        
        if available1 and available2:
            if t1 <= t2:
                t1 = max(a, t1) + R
            else:
                t2 = max(a, t2) + R
        elif available1:
            t1 = max(a, t2) + R
        else:
            t2 = max(a, t1) + R    
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
