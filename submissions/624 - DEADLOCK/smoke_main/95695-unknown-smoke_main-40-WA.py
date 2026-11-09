from collections import deque
def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE
    num_charges = N
    queue_charges = []

    for time in A:
        while queue_charges and queue_charges[0] <= time:
            num_charges += 1
            queue_charges.pop(0)

        if num_charges == 0:
            return "NO"

        num_charges -= 1

        if queue_charges:
            starting_point = queue_charges[-1]
        else:
            starting_point = time

        queue_charges.append(starting_point + R)

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
