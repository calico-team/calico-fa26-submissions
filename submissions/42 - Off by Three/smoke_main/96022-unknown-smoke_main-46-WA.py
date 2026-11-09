def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    charge=2
    recharge=0
    
    for i in A:

        while i>recharge and 2>charge:
            charge=charge+1
            recharge=recharge+R
                
        if charge ==0 :
            return "NO"
        
        charge=charge-1
        
        if charge==1:
            recharge=i+R

    return "yes"



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
