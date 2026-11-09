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

import sys ## for fast input reading
from math import isqrt ## exact integer square root

def solve(N, M, Q, earthquakes):
    ## Replay earthquakes from last to first; each block keeps the first value it gets, since that comes from the latest earthquake.
    W = M + 1 
    parent = list(range(N * W + 1)) 
    grid = [0] * (N * W) 

    def find(x):
        root = x
        while parent[root] != root:
            root = parent[root]
        while parent[x] != root:
            parent[x], x = root, parent[x]
        return root

    for R, C, P in reversed(earthquakes):
        PP = P * P
        for dr in range(-P, P + 1):
            w = isqrt(PP - dr * dr)
            base = (R + dr) * W
            hi = base + C + w
            i = find(base + C - w)
            while i <= hi:
                dc = i - base - C
                grid[i] = PP - (dr * dr + dc * dc) + 1
                parent[i] = i + 1
                i = find(i + 1)

    return [grid[r * W:r * W + M] for r in range(N)]


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