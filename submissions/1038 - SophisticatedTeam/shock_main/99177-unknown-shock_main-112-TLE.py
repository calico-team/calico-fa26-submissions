import math
import sys


def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return

    iterator = iter(input_data)
    T = int(next(iterator))

    out = []

    for _ in range(T):
        N = int(next(iterator))
        M = int(next(iterator))
        Q = int(next(iterator))

        grid = [[0] * M for _ in range(N)]

        max_dim = max(N, M)
        sq = [i * i for i in range(max_dim + 1)]

        for _ in range(Q):
            R = int(next(iterator))
            C = int(next(iterator))
            P = int(next(iterator))

            P2 = P * P
            P2_1 = P2 + 1

            for dr in range(P + 1):
                dr2 = sq[dr]
                rem = P2 - dr2
                max_dc = math.isqrt(rem)

                r1 = R + dr
                r2 = R - dr

                row1 = grid[r1]
                row2 = grid[r2]

                base = P2_1 - dr2

                row1[C] = base
                row2[C] = base

                for dc in range(1, max_dc + 1):
                    val = base - sq[dc]
                    c1 = C + dc
                    c2 = C - dc

                    row1[c1] = val
                    row1[c2] = val
                    row2[c1] = val
                    row2[c2] = val

        for row in grid:
            out.append(" ".join(map(str, row)))

    print("\n".join(out))


if __name__ == "__main__":
    solve()