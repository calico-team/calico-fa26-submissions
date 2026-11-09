import sys


def solve(N, R, A):
    t1 = 0
    t2 = 0
    count = 2

    for t in A:
        if count < 2 and t1 <= t:
            t1 = t2
            count += 1

        if count < 2 and t1 <= t:
            t1 = t2
            count += 1

        if count == 0:
            return "NO"

        count -= 1

        if count == 0:
            t1 = t + R
            t2 = t + 2 * R
        elif count == 1:
            t2 = t + R

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

    sys.stdout.write("\n".join(out))


if __name__ == "__main__":
    read_your_input()