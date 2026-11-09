
from math import isqrt


def solve(N, M, Q, earthquakes):

    W = M + 1
    total = N * W

    parent = list(range(total + 1))
    grid = [[0] * M for _ in range(N)]

    def find(x):
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x

    for X, Y, P in reversed(earthquakes):

        if X + P < 0 or X - P >= M:
            continue
        if Y + P < 0 or Y - P >= N:
            continue

        PP = P * P

        top = max(0, Y - P)
        bottom = min(N - 1, Y + P)

        for r in range(top, bottom + 1):

            dy = r - Y
            dy2 = dy * dy

            dx = isqrt(PP - dy2)

            left = max(0, X - dx)
            right = min(M - 1, X + dx)

            if left > right:
                continue

            base = r * W
            end = base + right

            pos = find(base + left)

            while pos <= end:

                c = pos - base
                ddx = c - X

                value = PP - dy2 - ddx * ddx + 1

                grid[r][c] = value
                parent[pos] = find(pos + 1)
                pos = parent[pos]

    return grid


def main():

    T = int(input())

    for _ in range(T):

        N, M, Q = map(int, input().split())

        earthquakes = []

        for _ in range(Q):
            X, Y, P = map(int, input().split())
            earthquakes.append((X, Y, P))

        answer = solve(N, M, Q, earthquakes)

        for row in answer:
            print(" ".join(map(str, row)))


if __name__ == "__main__":
    main()
