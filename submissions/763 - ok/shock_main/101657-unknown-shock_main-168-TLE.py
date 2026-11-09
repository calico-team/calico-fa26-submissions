import sys
import math

def solve():
    input = sys.stdin.readline

    T = int(input())

    for _ in range(T):
        N, M, Q = map(int, input().split())

        earthquakes = []

        for _ in range(Q):
            R, C, P = map(int, input().split())
            earthquakes.append((R, C, P))

        # Initialize readings
        ans = [0] * (N * M)

        # DSU: next unassigned column in each row
        parent = list(range(N * (M + 1)))

        def find(x):
            while parent[x] != x:
                parent[x] = parent[parent[x]]
                x = parent[x]
            return x

        # Process earthquakes in reverse order
        for R, C, P in reversed(earthquakes):

            p2 = P * P

            for r in range(R - P, R + P + 1):

                dx = r - R

                # Maximum horizontal distance
                dy = math.isqrt(p2 - dx * dx)

                left = C - dy
                right = C + dy

                base = r * (M + 1)
                end = base + right

                x = find(base + left)

                while x <= end:

                    c = x - base

                    dy2 = c - C

                    # Shock level
                    ans[r * M + c] = (
                        p2 - dx * dx - dy2 * dy2 + 1
                    )

                    # Mark this cell as assigned
                    parent[x] = find(x + 1)

                    x = parent[x]

        # Print result
        for r in range(N):
            start = r * M
            print(*ans[start:start + M])


if __name__ == "__main__":
    solve()