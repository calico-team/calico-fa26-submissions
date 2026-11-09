def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE
    back = []
    
    for t in A:
        while len(back) > 0 and back[0] <= t:
            back.pop(0)
        
        if len(back) ==2:
            return "NO"
        
        if len(back) == 0:
            start = t
        else:
            start = back[-1]
        
        back.append(start + R)
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
