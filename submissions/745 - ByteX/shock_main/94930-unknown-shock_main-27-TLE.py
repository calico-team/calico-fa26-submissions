
import sys
from math import isqrt

def solve():
    input = sys.stdin.buffer.readline
    t = int(input())

    for _ in range(t):
        n, m, q = map(int, input().split())

        events = [tuple(map(int, input().split())) for _ in range(q)]

        ans = [[0] * m for _ in range(n)]

        w = m + 1
        parent = list(range(n * w))

        def find(x):
            while parent[x] != x:
                parent[x] = parent[parent[x]]
                x = parent[x]
            return x

        for R, C, P in reversed(events):
            p2 = P * P

            for r in range(R - P, R + P + 1):
                dr = r - R
                dx = isqrt(p2 - dr * dr)

                base = r * w
                left = base + C - dx
                right = base + C + dx

                c = find(left)

                while c <= right:
                    col = c - base
                    dc = col - C

                    ans[r][col] = p2 - dr * dr - dc * dc + 1

                    parent[c] = find(c + 1)
                    c = parent[c]

        sys.stdout.write(
            '\n'.join(' '.join(map(str, row)) for row in ans) + '\n'
        )


if __name__ == "__main__":
    solve()
