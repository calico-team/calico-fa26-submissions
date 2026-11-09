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
def solve(N, M, Q, earthquakes):
    answer = [[0] * M for _ in range(N)]
    parent = [list(range(M + 1)) for _ in range(N)]
    
    def find(r, c):
        path = []
        current = c
        while parent[r][current] != current:
            path.append(current)
            current = parent[r][current]
        for p in path:
            parent[r][p] = current
        return current
    for i in range(Q - 1, -1, -1):
        X, Y, P = earthquakes[i]
        R, C = X, Y
        P2 = P * P
        
        r_min = max(0, R - P)
        r_max = min(N - 1, R + P)
        
        for r in range(r_min, r_max + 1):
            dy = r - R
            dy2 = dy * dy
            rem = P2 - dy2
            if rem < 0:
                continue
            dx_max = math.isqrt(rem)
            
            c_min = max(0, C - dx_max)
            c_max = min(M - 1, C + dx_max)
            
            c = find(r, c_min)
            while c <= c_max:
                dx = c - C
                dist2 = dy2 + dx * dx
                answer[r][c] = P2 - dist2 + 1
                parent[r][c] = find(r, c + 1)
                c = parent[r][c]
                
    return answer


def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    iterator = iter(input_data)
    
    T = int(next(iterator))
    out = []
    for _ in range(T):
        N = int(next(iterator))
        M = int(next(iterator))
        Q = int(next(iterator))
        
        earthquakes = []
        for _ in range(Q):
            X = int(next(iterator))
            Y = int(next(iterator))
            P = int(next(iterator))
            earthquakes.append((X, Y, P))
            
        answer = solve(N, M, Q, earthquakes)
        for row in answer:
            out.append(' '.join(map(str, row)))
            
    sys.stdout.write('\n'.join(out) + '\n')

if __name__ == '__main__':
    main()