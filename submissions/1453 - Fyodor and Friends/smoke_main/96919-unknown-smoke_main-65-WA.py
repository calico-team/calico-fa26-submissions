def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE
    smokes = 2
    cooldown = R
    for i in range(0, len(A)):
        
        if smokes != 2:
            cooldown -= (A[i] - A[i-1])
            
            if cooldown <= 0:
                if (cooldown <= -R and smokes == 0):
                    cooldown += R
                    smokes += 1
                cooldown += R
                smokes += 1

        smokes -= 1

        if smokes < 0:
            return "NO"

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
