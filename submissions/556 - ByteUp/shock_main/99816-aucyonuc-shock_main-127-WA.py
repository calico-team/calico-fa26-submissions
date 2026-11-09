
import sys
from math import isqrt


def solve(N, M, Q, earthquakes):
    ans = [[0] * M for _ in range(N)]

    parent = [list(range(M + 1)) for _ in range(N)]

    def find(row, x):
        p = parent[row]
        while p[x] != x:
            p[x] = p[p[x]]
            x = p[x]
        return x

    remaining = N * M

    for X, Y, P in reversed(earthquakes):
        if remaining == 0:
            break

        p2 = P * P
        top = max(0, Y - P)
        bottom = min(N - 1, Y + P)

        for r in range(top, bottom + 1):
            dy = r - Y
            dx = isqrt(p2 - dy * dy)

            left = max(0, X - dx)
            right = min(M - 1, X + dx)

            c = find(r, left)

            while c <= right:
                dist2 = dy * dy + (c - X) * (c - X)
                ans[r][c] = p2 - dist2 + 1

                parent[r][c] = find(r, c + 1)
                remaining -= 1

                c = find(r, c)

    return ans


def main():
    input = sys.stdin.readline

    T = int(input())

    for _ in range(T):
        N, M, Q = map(int, input().split())

        earthquakes = []
        for _ in range(Q):
            X, Y, P = map(int, input().split())
            earthquakes.append((X, Y, P))

        answer = solve(N, M, Q, earthquakes)

        for row in answer:
            print(' '.join(map(str, row)))


if __name__ == '__main__':
    main()
