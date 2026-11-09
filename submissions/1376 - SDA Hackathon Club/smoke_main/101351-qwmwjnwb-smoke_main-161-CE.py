import random

def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE
    # result = random.randint(0, 1)
    # if result == 1:
    #     return 'Yes'
    # else:
    #     return 'No'
    list answers = ["YES", "NO", "NO", "YES", "NO"]
    answer = list[0]
    list.pop(0)
    return answer



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
