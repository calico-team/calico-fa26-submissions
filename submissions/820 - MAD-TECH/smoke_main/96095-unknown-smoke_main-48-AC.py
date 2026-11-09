import time


def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE
    
def solve(N, R, A):
    available_charges = 2
    awaiting = []

    for timestamp in A:

        
        while awaiting and awaiting[0] <= timestamp:
            available_charges += 1
            awaiting.pop(0)

        
        if available_charges == 0:
            return "NO"

        
        available_charges -= 1

        
        if awaiting:
            charging_time = awaiting[-1] + R
        else:
            charging_time = timestamp + R

        awaiting.append(charging_time)

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
