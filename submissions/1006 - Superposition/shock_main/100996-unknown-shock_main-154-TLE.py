"""
*Return an N by M grid displaying the reading of the block seismometers after all earthquakes occur.
*
*N: number of rows in the grid
*M: number of columns in the grid
*Q: number of earthquakes
*earthquakes: a list of tuples (X, Y, P), where:
*    X: column of the epicenter
*    Y: row of the epicenter
*    P: power of the earthquake
"""
import math

def solve(N, M, Q, earthquakes):
    ans = [[0] * M for _ in range(N)]

    for R, C, P in reversed(earthquakes):
        r_start = R - P
        r_end = R + P

        for r in range(r_start, r_end + 1):
            dr = r - R
            dc = int(math.isqrt(P * P - dr * dr))

            c_start = C - dc
            c_end = C + dc

            for c in range(c_start, c_end + 1):
                dist_sq = dr * dr + (c - C) * (c - C)
                shock = P * P - dist_sq + 1

                if ans[r][c] == 0 or shock < ans[r][c]:
                    ans[r][c] = shock

    return ans


def main():
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