
import sys
from math import isqrt
from array import array


def solve():
    data = iter(map(int, sys.stdin.buffer.read().split()))
    T = next(data)

    results = []

    for _ in range(T):
        N = next(data)
        M = next(data)
        Q = next(data)

        earthquakes = []

        for _ in range(Q):
            R = next(data)
            C = next(data)
            P = next(data)
            earthquakes.append((R, C, P))

        # Each row has M columns plus one sentinel.
        stride = M + 1
        parent = array('i', range(N * stride))

        ans = [0] * (N * M)

        def find(x):
            while parent[x] != x:
                parent[x] = parent[parent[x]]
                x = parent[x]
            return x

        # Process earthquakes from latest to earliest.
        for R, C, P in reversed(earthquakes):
            p2 = P * P

            for r in range(R - P, R + P + 1):
                dy = r - R
                remaining = p2 - dy * dy
                dx = isqrt(remaining)

                left = C - dx
                right = C + dx

                base = r * stride

                # Jump to the first unassigned column.
                x = find(base + left)
                end = base + right

                while x <= end:
                    c = x - base

                    distance2 = dy * dy + (c - C) * (c - C)
                    ans[r * M + c] = p2 - distance2 + 1

                    # Remove this column from future consideration.
                    nxt = find(x + 1)
                    parent[x] = nxt
                    x = nxt

        # Build output.
        for r in range(N):
            start = r * M
            results.append(" ".join(map(str, ans[start:start + M])))

    sys.stdout.write("\n".join(results))


if __name__ == "__main__":
    solve()
