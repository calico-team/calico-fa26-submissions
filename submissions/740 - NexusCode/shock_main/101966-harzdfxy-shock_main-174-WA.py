"""
*Return an N by M grid displaying the reading of the block seismometers after all earthquakes occur.
*
*N: number of rows in the grid
*M: number of columns in the grid
*Q: number of earthquakes
*earthquakes: a list of tuples (X, Y, P), where:
-    X: column of the epicenter
-    Y: row of the epicenter
-    P: power of the earthquake
"""
import math

def solve(N, M, Q, earthquakes):
    grid = [[0] * M for _ in range(N)]
    
    for X, Y, P in earthquakes:
        r_c = Y
        c_c = X
        P2 = P * P
        
        r_min = max(0, r_c - P)
        r_max = min(N - 1, r_c + P)
        
        for r in range(r_min, r_max + 1):
            dr = r - r_c
            dr2 = dr * dr
            max_dc = int(math.isqrt(P2 - dr2))
            
            c_min = max(0, c_c - max_dc)
            c_max = min(M - 1, c_c + max_dc)
            
            for c in range(c_min, c_max + 1):
                dc = c - c_c
                grid[r][c] = P2 - (dr2 + dc * dc) + 1
                
    return grid


def main():
    import sys
    input = sys.stdin.read
    data = input().split()
    if not data:
        return
    
    it = iter(data)
    T = int(next(it))
    for _ in range(T):
        N = int(next(it))
        M = int(next(it))
        Q = int(next(it))
        earthquakes = []
        for _ in range(Q):
            X = int(next(it))
            Y = int(next(it))
            P = int(next(it))
            earthquakes.append((X, Y, P))
        answer = solve(N, M, Q, earthquakes)
        for row in answer:
            print(' '.join(map(str, row)))

if __name__ == '__main__':
    main()