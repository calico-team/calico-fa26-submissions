from collections import deque
def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE
    ironman=2
    avengers=deque()
    for thanos in A:
        while avengers and avengers[0] <= thanos:
            avengers.popleft()
            ironman+=1
        if ironman==0:
            return "NO"
        ironman -= 1
        if avengers:
            infinite = avengers[-1] + R
        else:
            infinite=thanos+R
        avengers.append(infinite)
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
