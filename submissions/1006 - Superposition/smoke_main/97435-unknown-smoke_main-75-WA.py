def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE
    #charge = 2
    #recharge_time = 0
    
    
    ready1 = 0
    ready2 = 0
    for timestamp in A:
        #temp fix
        if ready2 < ready1:
            ready1, ready2 = ready2, ready1
        
        if ready1 < timestamp:
            ready1 = max(ready2, timestamp) + R
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
