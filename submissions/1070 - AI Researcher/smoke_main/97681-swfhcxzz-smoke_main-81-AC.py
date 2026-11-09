def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    first_smoke_charge = 0
    second_smoke_charge = 0
    
    for time in A:
        if first_smoke_charge > second_smoke_charge:
            first_smoke_charge, second_smoke_charge = second_smoke_charge, first_smoke_charge
    
        if first_smoke_charge > time:
            return "NO"
    
        first_smoke_charge = second_smoke_charge
        second_smoke_charge = max(time, second_smoke_charge) + R
    
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
