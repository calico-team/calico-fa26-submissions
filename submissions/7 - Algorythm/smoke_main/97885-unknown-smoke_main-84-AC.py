
def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    queue = []

    for t in A:

        # Process all completed recharges
        while queue and queue[0] <= t:
            queue.pop(0)

        # If both charges are recharging, no smoke is available
        if len(queue) == 2:
            return "NO"

        # Schedule the recharge of the used smoke
        if queue:
            queue.append(queue[-1] + R)
        else:
            queue.append(t + R)

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
