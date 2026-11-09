from collections import deque
def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    charges=2
    recharge=deque()
    for i in A:
        while recharge and recharge[0]<=i:
            recharge.popleft()
            charges+=1

        if charges==0:
            return "NO"

        charges-=1

        if recharge:
            recharge.append(recharge[-1]+R)
        else:
            recharge.append(i+R)
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
