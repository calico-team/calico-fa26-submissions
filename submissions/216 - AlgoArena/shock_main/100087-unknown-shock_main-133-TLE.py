def solve(N, M, Q, earthquakes):
    """
    Return an N by M grid displaying the reading of the block seismometers after all earthquakes occur.
    
    N: number of rows in the grid
    M: number of columns in the grid
    Q: number of earthquakes
    earthquakes: a list of tuples (X, Y, P), where:
        X: column of the epicenter
        Y: row of the epicenter
        P: power of the earthquake
    """
    res = [[0] * M for _ in range(N)]
    done = [[False] * M for _ in range(N)] 
    for r_c, c_c, pow_val in reversed(earthquakes):
        p2 = pow_val * pow_val  
        r1 = max(0, r_c - pow_val)
        r2 = min(N - 1, r_c + pow_val)
        for r in range(r1, r2 + 1):
            dy = r - r_c
            dy2 = dy * dy
            if dy2 > p2:
                continue      
            dx_lim = int((p2 - dy2) ** 0.5)
            c1 = max(0, c_c - dx_lim)
            c2 = min(M - 1, c_c + dx_lim)
            row_done = done[r]
            row_res = res[r]
            for c in range(c1, c2 + 1):
                if not row_done[c]:
                    row_done[c] = True
                    dx = c - c_c
                    row_res[c] = p2 - (dy2 + dx * dx) + 1
    return res
def main():
    import sys
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    iterator = iter(input_data)
    T = int(next(iterator))
    for _ in range(T):
        N = int(next(iterator))
        M = int(next(iterator))
        Q = int(next(iterator))
        earthquakes = []
        for _ in range(Q):
            R = int(next(iterator))
            C = int(next(iterator))
            P = int(next(iterator))
            earthquakes.append((R, C, P))               
        answer = solve(N, M, Q, earthquakes)
        out_lines = []
        for row in answer:
            out_lines.append(' '.join(map(str, row)))
        sys.stdout.write('\n'.join(out_lines) + '\n')
if __name__ == '__main__':
    main()