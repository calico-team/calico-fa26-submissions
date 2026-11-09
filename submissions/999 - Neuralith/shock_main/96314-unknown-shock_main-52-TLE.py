
import sys
from math import isqrt


def solve():
    input = sys.stdin.buffer.readline
    T = int(input())

    output = []

    for _ in range(T):
        N, M, Q = map(int, input().split())

        earthquakes = [
            tuple(map(int, input().split()))
            for _ in range(Q)
        ]

        stride = M + 1
        total = N * stride

        parent = list(range(total))
        remaining = [M] * N
        ans = [0] * (N * M)

        def find(x):
            p = parent
            while p[x] != x:
                p[x] = p[p[x]]
                x = p[x]
            return x

        for R, C, P in reversed(earthquakes):
            p2 = P * P

            for r in range(R - P, R + P + 1):
                if remaining[r] == 0:
                    continue

                dy = r - R
                dx = isqrt(p2 - dy * dy)

                base = r * stride
                left = base + C - dx
                right = base + C + dx

                x = find(left)

                while x <= right:
                    c = x - base

                    dc = c - C
                    ans[r * M + c] = p2 - dy * dy - dc * dc + 1

                    remaining[r] -= 1

                    # Remove this position from the available set.
                    parent[x] = find(x + 1)
                    x = parent[x]

        for r in range(N):
            start = r * M
            output.append(" ".join(map(str, ans[start:start + M])))

    sys.stdout.write("\n".join(output))


if __name__ == "__main__":
    solve()
