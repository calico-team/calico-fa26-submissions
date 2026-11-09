from collections import deque

def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE
    charges = 2
    recharge_queue =deque()
    
    for t in A:
        while recharge_queue and recharge_queue[0] <= t:
            recharge_queue.popleft()
            charges += 1
    
        if charges == 0:
            return "NO"
    
        charges -= 1
    
        if recharge_queue:
            finish_time = recharge_queue[-1] + R
        else:
            finish_time = t + R
        recharge_queue.append(finish_time)

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
