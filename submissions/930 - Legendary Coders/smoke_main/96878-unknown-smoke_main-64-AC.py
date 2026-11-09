def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    available = 2
    recharge_time = []
    next_recharge = 0
    last_finish = 0
    for t in A:
        while next_recharge < len(recharge_time) and recharge_time[next_recharge] <=t:
            available +=1
            next_recharge += 1
        if available == 0:
            return "NO"
        available -=1
        finish = max(t, last_finish) + R
        recharge_time.append(finish)
        last_finish = finish
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
