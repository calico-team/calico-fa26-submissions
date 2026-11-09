
import sys
from array import array
from math import isqrt

def solve():
    data = iter(map(int, sys.stdin.buffer.read().split()))
    T = next(data)
    output = []

    def find(parent, x):
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x

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

        stride = M + 1

        # Store answers and DSU using compact integer arrays
        ans = array('i', [0]) * (N * M)
        parent = array('i', range(N * stride))

        # Process earthquakes from newest to oldest
        for R, C, P in reversed(earthquakes):
            p2 = P * P

            for r in range(R - P, R + P + 1):
                dr = r - R
                reach = isqrt(p2 - dr * dr)

                left = C - reach
                right = C + reach

                base = r * stride

                # Find first unprocessed column
                c = find(parent, base + left) - base

                while c <= right:
                    idx = base + c
                    dc = c - C

                    # Assign the latest earthquake's shock
                    ans[r * M + c] = (
                        p2 - dr * dr - dc * dc + 1
                    )

                    # Remove this cell from future processing
                    parent[idx] = find(parent, idx + 1)

                    c = parent[idx] - base

        # Build output
        for r in range(N):
            start = r * M
            output.append(
                " ".join(map(str, ans[start:start + M]))
            )

    sys.stdout.write("\n".join(output))


if __name__ == "__main__":
    solve()
