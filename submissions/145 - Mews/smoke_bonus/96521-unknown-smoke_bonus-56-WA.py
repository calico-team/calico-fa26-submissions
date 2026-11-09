import sys


def solve(N, R, A):
    recharge = []

    for t in A:
        if recharge and recharge[0] <= t:
            recharge.pop(0)

        if len(recharge) >= 2:
            return "NO"

        recharge.append(t + R)
        recharge.sort()

    return "YES"


def read_your_input():
    data = list(map(int, sys.stdin.buffer.read().split()))
    pos = 0

    T = data[pos]
    pos += 1

    out = []

    for _ in range(T):
        N, R = data[pos], data[pos + 1]
        pos += 2

        A = data[pos:pos + N]
        pos += N

        out.append(solve(N, R, A))

    print("\n".join(out))


if __name__ == "__main__":
    read_your_input()