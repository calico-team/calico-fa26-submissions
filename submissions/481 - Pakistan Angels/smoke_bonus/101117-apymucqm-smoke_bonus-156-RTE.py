def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE
    
    smoke_charge_1 = 0
    smoke_charge_2 = 0
    
    answer = "YES"
    
    for time in A:
        if smoke_charge_1 <= time and smoke_charge_2 <= time:
            
                if smoke_charge_1 <= smoke_charge_2:
                    smoke_charge_1 = time + R
                else:
                    smoke_charge_2 = time + R
	
        elif smoke_charge_1 <= time:
                smoke_charge_1 = smoke_charge_2 + R
                
        elif smoke_charge_2 <= time:
                smoke_charge_2 = smoke_charge_1 + R
        else:
                answer = "NO"
                break
    return answer



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
