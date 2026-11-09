import sys

def solve():
    input = sys.stdin.readline
    T = int(input())

    for _ in range(T):
        N, R = map(int, input().split())
        A = list(map(int, input().split()))

        recharge = [0, 0]
        possible = True

        for t in A:
            if recharge[0] <= t:
                recharge[0] = t + R
            elif recharge[1] <= t:
                recharge[1] = recharge[0] + R
                recharge[0] = recharge[0] + R
            else:
                possible = False
                break

        print("YES" if possible else "NO")


if __name__ == "__main__":
    solve()