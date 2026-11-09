def solve(N, R, A):
    charges = 2
    recharge = []
    for t in A:
        while recharge and recharge[0] <= t:
            recharge.pop(0)
            charges += 1
        if charges == 0:
            return "NO"
        charges -= 1
        if recharge:
            finish = recharge[-1] + R
        else:
            finish = t + R
        recharge.append(finish)
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
