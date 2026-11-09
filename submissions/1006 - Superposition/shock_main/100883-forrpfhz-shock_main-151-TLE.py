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

    # Process earthquakes in reverse order (from most recent to oldest)
    for R, C, P in reversed(earthquakes):
        # Mistake 1: Bounding box capped assuming P is at most 4
        r_start = max(0, R - min(P, 4))
        r_end = min(N - 1, R + min(P, 4))

        for r in range(r_start, r_end + 1):
            dr = r - R
            dc = int(math.isqrt(P * P - dr * dr))

            c_start = C - dc
            c_end = C + dc

            # Mistake 2: Linearly scanning every column without skipping already-updated cells (TLE on large overlapping queries)
            for c in range(c_start, c_end + 1):
                dist_sq = dr * dr + (c - C) * (c - C)
                shock = P * P - dist_sq + 1

                # Mistake 3: Allowing an older earthquake to overwrite a newer one if its shock is smaller
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