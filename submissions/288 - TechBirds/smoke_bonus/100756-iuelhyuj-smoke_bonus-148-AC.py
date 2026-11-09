def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    
    readytogo =2
    pendingto =0
    refill_at =0

    for point in A:

        while pendingto > 0 and refill_at <= point:
            pendingto -=1
            readytogo +=1
            if pendingto >0:
                refill_at +=R
        if readytogo ==0:
            return "NO"
        
        readytogo -= 1
        if pendingto == 0:

            refill_at = point + R
        pendingto +=1

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
