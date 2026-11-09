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
    # parent[r][c] points to the next unvisited column >= c in row r
    parent = [list(range(M + 1)) for _ in range(N)]

    for R, C, P in reversed(earthquakes):
        r_start = R - P
        r_end = R + P
        P_sq_plus_1 = P * P + 1

        for r in range(r_start, r_end + 1):
            dr = r - R
            dr_sq = dr * dr
            dc = math.isqrt(P * P - dr_sq)

            c_start = C - dc
            c_end = C + dc

            ans_r = ans[r]
            par_r = parent[r]
            base_shock = P_sq_plus_1 - dr_sq

            # Find first unvisited column >= c_start with path halving
            c = c_start
            while par_r[c] != c:
                par_r[c] = par_r[par_r[c]]
                c = par_r[c]

            while c <= c_end:
                dc_cur = c - C
                ans_r[c] = base_shock - dc_cur * dc_cur

                # Mark column c as visited by pointing it to par_r[c + 1]
                nxt = par_r[c + 1]
                while par_r[nxt] != nxt:
                    par_r[nxt] = par_r[par_r[nxt]]
                    nxt = par_r[nxt]
                par_r[c] = nxt
                c = nxt

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