import sys
from math import isqrt

def solve(N, M, Q, earthquakes):
    grid = [[0] * M for _ in range(N)]
    nxt = [list(range(M + 1)) for _ in range(N)]
    max_p = {}

    for R, C, P in reversed(earthquakes):
        if max_p.get((R, C), -1) >= P:
            continue
        max_p[(R, C)] = P
        P2 = P * P
        for r in range(R - P, R + P + 1):
            rem = P2 - (r - R) * (r - R)
            dx = isqrt(rem)
            L, U = C - dx, C + dx
            row_g = grid[r]
            row_n = nxt[r]
            base = rem + 1
            c = L
            while c <= U:
                nc = row_n[c]
                if nc == c:
                    row_g[c] = base - (c - C) * (c - C)
                    row_n[c] = row_n[ U + 1 ]
                    c += 1
                else:
                    row_n[c] = row_n[nc]
                    c = nc

    return grid


def main():
    input = sys.stdin.readline
    T = int(input())
    for _ in range(T):
        N, M, Q = map(int, input().split())
        earthquakes = []
        for i in range(Q):
            X, Y, P = map(int, input().split())
            earthquakes.append((X, Y, P))
        answer = solve(N, M, Q, earthquakes)
        for row in answer:
            print(' '.join(map(str, row)))

if __name__ == '__main__':
    main()