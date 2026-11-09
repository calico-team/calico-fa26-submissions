
import sys
from math import isqrt


def solve(N, M, Q, earthquakes):
    ans = [[0] * M for _ in range(N)]
    parent = [list(range(M + 1)) for _ in range(N)]

    def find(r, c):
        p = parent[r]
        while p[c] != c:
            p[c] = p[p[c]]
            c = p[c]
        return c

    remaining = N * M

    for R, C, P in reversed(earthquakes):
        if remaining == 0:
            break

        p2 = P * P

        for r in range(R - P, R + P + 1):
            dy = r - R
            dx = isqrt(p2 - dy * dy)

            left = C - dx
            right = C + dx

            c = find(r, left)

            while c <= right:
                dist2 = dy * dy + (c - C) ** 2
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
            R, C, P = map(int, input().split())
            earthquakes.append((R, C, P))

        answer = solve(N, M, Q, earthquakes)

        for row in answer:
            print(' '.join(map(str, row)))


if __name__ == '__main__':
    main()
