def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    currentSmokeBuffer = 1

    rechargeAt = [0, 0]

    for i in range(N):
        if A[i] >= rechargeAt[0] and rechargeAt[0] != 0:
            if currentSmokeBuffer < 2:
                currentSmokeBuffer += 1
            rechargeAt[0] = rechargeAt[1]
            rechargeAt[1] = 0

        if currentSmokeBuffer == 0:
            return "NO"

        if currentSmokeBuffer > 0:
            currentSmokeBuffer -= 1

            if rechargeAt[0] == 0:
                rechargeAt[0] = A[i] + R
            elif rechargeAt[1] == 0:
                rechargeAt[1] = rechargeAt[0] + R

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
