import sys
from math import isqrt


def solve(N, M, Q, quakes):
    W = M + 1
    nxt = list(range(N * W))
    grid = [0] * (N * W)
    remaining = N * M
    for qi in range(Q - 1, -1, -1):
        if remaining <= 0:
            break
        R, C, P = quakes[qi]
        PP = P * P
        for dr in range(0, P + 1):
            w = isqrt(PP - dr * dr)
            rows = (R,) if dr == 0 else (R - dr, R + dr)
            base_val = PP - dr * dr + 1
            for r in rows:
                base = r * W
                lo = base + C - w
                hi = base + C + w
                # find(lo)
                i = lo
                while nxt[i] != i:
                    nxt[i] = nxt[nxt[i]]
                    i = nxt[i]
                while i <= hi:
                    dc = i - base - C
                    grid[i] = base_val - dc * dc
                    remaining -= 1
                    nxt[i] = i + 1
                    j = i + 1
                    while nxt[j] != j:
                        nxt[j] = nxt[nxt[j]]
                        j = nxt[j]
                    i = j
    out = []
    for r in range(N):
        out.append(" ".join(map(str, grid[r * W:r * W + M])))
    return "\n".join(out)


def read_your_input():
    data = sys.stdin.buffer.read().split()
    pos = 0
    T = int(data[pos]); pos += 1
    res = []
    for _ in range(T):
        N = int(data[pos]); M = int(data[pos + 1]); Q = int(data[pos + 2]); pos += 3
        quakes = []
        for _ in range(Q):
            quakes.append((int(data[pos]), int(data[pos + 1]), int(data[pos + 2])))
            pos += 3
        res.append(solve(N, M, Q, quakes))
    sys.stdout.write("\n".join(res) + "\n")


if __name__ == "__main__":
    read_your_input()