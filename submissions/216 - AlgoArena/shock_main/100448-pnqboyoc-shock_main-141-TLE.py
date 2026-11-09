import sys


def solve(N, M, Q, earthquakes):
    # Flatten the visited/done grid into a 1D array for maximum speed
    total_cells = N * M
    done = [False] * total_cells
    res = [0] * total_cells
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
            row_offset = r * M
            for c in range(c1, c2 + 1):
                idx = row_offset + c
                if not done[idx]:
                    done[idx] = True
                    dx = c - c_c
                    res[idx] = p2 - (dy2 + dx * dx) + 1
    return [res[i * M:(i + 1) * M] for i in range(N)]
def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    iterator = iter(input_data)
    T = int(next(iterator))
    out_lines = []
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
        for row in answer:
            out_lines.append(' '.join(map(str, row)))
    sys.stdout.write('\n'.join(out_lines) + '\n')
if __name__ == '__main__':
    main()