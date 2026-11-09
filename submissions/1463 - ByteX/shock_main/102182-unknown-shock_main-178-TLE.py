
from math import isqrt


def solve(N, M, Q, earthquakes):

    W = M + 1
    total = N * W

    # DSU to skip already processed cells
    parent = list(range(total + 1))

    # Final readings
    result = [0] * (N * M)

    def find(x):
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x

    # Latest earthquake first
    for R, C, P in reversed(earthquakes):

        P2 = P * P

        # All affected rows are inside the grid
        # according to the problem constraints.
        for r in range(R - P, R + P + 1):

            dy = r - R
            dy2 = dy * dy

            # Maximum horizontal distance
            dx = isqrt(P2 - dy2)

            left = C - dx
            right = C + dx

            base = r * W
            end = base + right

            # First cell not already processed
            pos = find(base + left)

            while pos <= end:

                c = pos - base
                dc = c - C

                # Shock level
                value = P2 - dy2 - dc * dc + 1

                result[r * M + c] = value

                # Mark this cell as processed
                parent[pos] = find(pos + 1)

                # Jump to next unprocessed cell
                pos = parent[pos]

    return result


def main():

    T = int(input())

    for _ in range(T):

        N, M, Q = map(int, input().split())

        earthquakes = []

        for _ in range(Q):
            R, C, P = map(int, input().split())
            earthquakes.append((R, C, P))

        answer = solve(N, M, Q, earthquakes)

        for r in range(N):
            start = r * M
            end = start + M

            print(*answer[start:end])


if __name__ == "__main__":
    main()
