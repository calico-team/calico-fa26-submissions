
import sys
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

        ans = [[0] * M for _ in range(N)]

        # Successor DSU for each row
        parent = [list(range(M + 1)) for _ in range(N)]

        # Process earthquakes in reverse order
        for R, C, P in reversed(earthquakes):
            p2 = P * P

            for r in range(R - P, R + P + 1):
                dr = r - R
                reach = isqrt(p2 - dr * dr)

                left = C - reach
                right = C + reach

                par = parent[r]
                c = find(par, left)

                while c <= right:
                    dc = c - C

                    # Latest earthquake that affects this cell
                    ans[r][c] = p2 - dr * dr - dc * dc + 1

                    # Mark this cell as already processed
                    par[c] = find(par, c + 1)
                    c = par[c]

        for row in ans:
            output.append(" ".join(map(str, row)))

    sys.stdout.write("\n".join(output))


if __name__ == "__main__":
    solve()
