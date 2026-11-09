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
def solve(N, M, Q, earthquakes):
    res = [[0] * M for _ in range(N)]
    done = [[False] * M for _ in range(N)]
    for i in range(Q - 1, -1, -1):
        x_c, y_r, pow_val = earthquakes[i]
        p2 = pow_val * pow_val  
        r1 = max(0, y_r - pow_val)
        r2 = min(N - 1, y_r + pow_val)
        for r in range(r1, r2 + 1):
            dy = r - y_r
            dy2 = dy * dy
            if dy2 > p2:
                continue      
            dx_lim = int((p2 - dy2) ** 0.5)
            c1 = max(0, x_c - dx_lim)
            c2 = min(M - 1, x_c + dx_lim)
            for c in range(c1, c2 + 1):
                if not done[r][c]:
                    done[r][c] = True
                    dx = c - x_c
                    res[r][c] = p2 - (dy2 + dx * dx) + 1
    return res
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