import math
import sys

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

# Precompute (dc, base_shock) tables across test cases for each radius P
_DC_CACHE = {}

def solve(N, M, Q, earthquakes):
    swap = False
    if N > M:
        N, M = M, N
        swap = True

    ans = [[0] * M for _ in range(N)]
    parent = [list(range(M + 1)) for _ in range(N)]
    row_par = list(range(N + 1))
    row_rem = [M] * N
    max_p = [[-1] * M for _ in range(N)]
    total_rem = N * M

    dc_cache = _DC_CACHE
    isqrt = math.isqrt

    for R, C, P in reversed(earthquakes):
        if total_rem == 0:
            break
        if swap:
            R, C = C, R
        if P <= max_p[R][C]:
            continue
        max_p[R][C] = P

        dcs = dc_cache.get(P)
        if dcs is None:
            P_sq = P * P
            P_sq_1 = P_sq + 1
            dcs = [(isqrt(P_sq - dr * dr), P_sq_1 - dr * dr) for dr in range(-P, P + 1)]
            dc_cache[P] = dcs

        r_start = R - P
        r_end = R + P
        offset = P - R

        r = row_par[r_start]
        while row_par[r] != r:
            row_par[r] = row_par[row_par[r]]
            r = row_par[r]
        row_par[r_start] = r

        while r <= r_end:
            dc, base_shock = dcs[r + offset]
            c_start = C - dc
            c_end = C + dc

            par_r = parent[r]
            c = par_r[c_start]
            if c <= c_end:
                while par_r[c] != c:
                    par_r[c] = par_r[par_r[c]]
                    c = par_r[c]
                if c <= c_end:
                    ans_r = ans[r]
                    rem = row_rem[r]
                    after_end = par_r[c_end + 1]
                    while par_r[after_end] != after_end:
                        par_r[after_end] = par_r[par_r[after_end]]
                        after_end = par_r[after_end]
                    par_r[c_start] = after_end
                    while c <= c_end:
                        dc_cur = c - C
                        ans_r[c] = base_shock - dc_cur * dc_cur
                        rem -= 1
                        nxt = par_r[c + 1]
                        par_r[c] = after_end
                        c = nxt
                    total_rem -= (row_rem[r] - rem)
                    row_rem[r] = rem
                    if rem == 0:
                        row_par[r] = row_par[r + 1]
                else:
                    par_r[c_start] = c

            nxt_r = row_par[r + 1]
            while row_par[nxt_r] != nxt_r:
                row_par[nxt_r] = row_par[row_par[nxt_r]]
                nxt_r = row_par[nxt_r]
            r = nxt_r

    if swap:
        ans = [list(col) for col in zip(*ans)]
    return ans


def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    it = iter(map(int, input_data))
    T = next(it)
    out = []
    for _ in range(T):
        N = next(it)
        M = next(it)
        Q = next(it)
        earthquakes = [(next(it), next(it), next(it)) for _ in range(Q)]
        answer = solve(N, M, Q, earthquakes)
        for row in answer:
            out.append(' '.join(map(str, row)))
    sys.stdout.write('\n'.join(out) + '\n')

if __name__ == '__main__':
    main()