import sys


def solve(N, R, A):
    charges = 2
    nxt = 0
    for t in A:
        while charges < 2 and nxt <= t:
            charges += 1
            nxt += R
        if charges == 0:
            return "NO"
        if charges == 2:
            nxt = t + R
        charges -= 1
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
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    read_your_input()