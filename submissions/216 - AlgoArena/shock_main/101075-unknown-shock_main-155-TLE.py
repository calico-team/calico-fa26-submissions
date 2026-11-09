import sys


def solve(N, M, Q, earthquakes):
    result = [[0] * M for _ in range(N)]
    next_unvisited = [list(range(M + 1)) for _ in range(N)]

    def find_next(row, column):
        parent = next_unvisited[row]
        root = column
        while parent[root] != root:
            root = parent[root]
        while parent[column] != column:
            following = parent[column]
            parent[column] = root
            column = following
        return root

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
            c = find_next(r, c1)
            while c <= c2:
                dx = c - c_c
                result[r][c] = p2 - (dy2 + dx * dx) + 1
                next_unvisited[r][c] = find_next(r, c + 1)
                c = find_next(r, c)
    return result
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