
def solve(N, R, A):
    charges = 2
    next_recharge = -1

    for t in A:
        while next_recharge != -1 and next_recharge <= t:
            charges += 1

            if charges == 2:
                next_recharge = -1
            else:
                next_recharge += R

        if charges == 0:
            return "NO"

        if charges == 2:
            next_recharge = t + R

        charges -= 1

    return "YES"


def main():
    T = int(input())

    for _ in range(T):
        N, R = map(int, input().split())
        A = list(map(int, input().split()))
        print(solve(N, R, A))


if __name__ == "__main__":
    main()
