
import sys

input = sys.stdin.readline

T = int(input())

for _ in range(T):
    N, M, Q = map(int, input().split())

    # Initially all seismometers read 0
    ans = [[0] * M for _ in range(N)]

    # Process earthquakes in chronological order
    for _ in range(Q):
        R, C, P = map(int, input().split())

        p2 = P * P

        for r in range(R - P, R + P + 1):
            dr2 = (r - R) ** 2

            for c in range(C - P, C + P + 1):
                dc2 = (c - C) ** 2
                dist2 = dr2 + dc2

                if dist2 <= p2:
                    shock = p2 - dist2 + 1
                    ans[r][c] = shock

    # Print final readings
    for row in ans:
        print(*row)
