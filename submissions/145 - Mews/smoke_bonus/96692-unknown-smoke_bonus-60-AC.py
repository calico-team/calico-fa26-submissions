import sys
from collections import deque


def solve(N, R, A):
    ready = deque()
    for t in A:
        while ready and ready[0] <= t:
            ready.popleft()
        if len(ready) >= 2:
            return "NO"
        start = ready[-1] if ready else t
        ready.append(start + R)
    return "YES"


def read_your_input():
    data = sys.stdin.buffer.read().split()
    pos = 0
    T = int(data[pos])
    pos += 1
    out = []
    for _ in range(T):
        N = int(data[pos])
        R = int(data[pos + 1])
        pos += 2
        A = [int(x) for x in data[pos:pos + N]]
        pos += N
        out.append(solve(N, R, A))
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    read_your_input()