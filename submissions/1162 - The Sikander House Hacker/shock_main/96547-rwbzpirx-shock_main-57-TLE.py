import sys

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    iterator = iter(input_data)
    T = int(next(iterator))
    for _ in range(T):
        N = int(next(iterator))
        M = int(next(iterator))
        Q = int(next(iterator))
        grid = [[0] * M for _ in range(N)]
        for _ in range(Q):
            r_e = int(next(iterator))
            c_e = int(next(iterator))
            p_e = int(next(iterator))
            p_sq = p_e * p_e
            r_min = max(0, r_e - p_e)
            r_max = min(N - 1, r_e + p_e)
            c_min = max(0, c_e - p_e)
            c_max = min(M - 1, c_e + p_e)
            for r in range(r_min, r_max + 1):
                row_g = grid[r]
                r_diff_sq = (r - r_e) ** 2
                for c in range(c_min, c_max + 1):
                    dist_sq = r_diff_sq + (c - c_e) ** 2
                    if dist_sq <= p_sq:
                        row_g[c] = p_sq - dist_sq + 1
        for row in grid:
            print(" ".join(map(str, row)))

if __name__ == "__main__":
    main()