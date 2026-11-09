def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE
    charge = 2 
    prev = A[0]
    for i in range(N):
        diff = A[i] - prev
        
        if diff >= R and charge < 2:
            charge += 1

        if charge == 0:
            return "NO"
        
        charge -= 1
        prev = A[i]
    
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
