
def solve(N, R, A):
    available = 2
    recharge = []
    j = 0

    for t in A:

        while j < len(recharge) and recharge[j] <= t:
            available += 1
            j += 1

        if available == 0:
            return "NO"

        available -= 1

        if j < len(recharge):
            recharge.append(recharge[-1] + R)
        else:
            recharge.append(t + R)

    return "YES"


def main():
    T = int(input())

    for _ in range(T):
        N, R = map(int, input().split())
        A = list(map(int, input().split()))

        print(solve(N, R, A))


if __name__ == '__main__':
    main()
