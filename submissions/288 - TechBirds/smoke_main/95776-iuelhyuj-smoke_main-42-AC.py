def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    TotalCharges =2
    Readyat =0
    for b in A:
        while TotalCharges <2 and Readyat <= b:
            TotalCharges +=1
            if TotalCharges < 2:
                Readyat +=R 
        if TotalCharges == 0:
            return "NO"
        if TotalCharges == 2:
            Readyat = b + R
        TotalCharges -=1       
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
