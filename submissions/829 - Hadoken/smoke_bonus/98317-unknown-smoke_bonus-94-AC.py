def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """

    
    first_charge = 0  
    second_charge = 0  

    for time in A:
        for i in range(2):
            if first_charge != 0:
                if first_charge <= time:
                    first_charge = second_charge
                    second_charge = 0
       
        if second_charge != 0:
            return "NO"

        if first_charge == 0:
            first_charge = time + R  


        else:
            second_charge = first_charge + R     

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
