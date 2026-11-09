def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE
    s1 = 0
    s2 = 0
    a = "YES"
    
    for i in A:
        
        if s1 > i:
            a = "NO"
            break
        n = max(t, s2) + R
        s1 = s2
        s2 = n
    return "".join(a)


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
