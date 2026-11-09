import sys

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    it = iter(input_data)
    T = int(next(it))
    out = []
    for _ in range(T):
        N = int(next(it))
        M = int(next(it))
        Q = int(next(it))
        grid = [[0] * M for _ in range(N)]
        for _ in range(Q):
            r_e = int(next(it))
            c_e = int(next(it))
            p_e = int(next(it))
            p_sq = p_e * p_e
            r_min = 0 if r_e < p_e else r_e - p_e
            r_max = N - 1 if r_e + p_e >= N else r_e + p_e
            c_min = 0 if c_e < p_e else c_e - p_e
            c_max = M - 1 if c_e + p_e >= M else c_e + p_e
            for r in range(r_min, r_max + 1):
                row_g = grid[r]
                rd2 = (r - r_e) * (r - r_e)
                for c in range(c_min, c_max + 1):
                    d2 = rd2 + (c - c_e) * (c - c_e)
                    if d2 <= p_sq:
                        row_g[c] = p_sq - d2 + 1
        for row in grid:
            out.append(" ".join(map(str, row)))
    sys.stdout.write("\n".join(out) + "\n")

if __name__ == '__main__':
    main()