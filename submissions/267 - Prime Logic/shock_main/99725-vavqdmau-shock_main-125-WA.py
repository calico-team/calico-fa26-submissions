import sys
from bisect import bisect_left, bisect_right
from math import isqrt

def solve(N,M,Q, earthquakes):
    if min(N, M) < 3:
        grid = [[0]*M for _ in range(N)]
        for r,c,p in earthquakes:
            grid[r][c] = 1
        return grid

    flip = M > N
    if flip:
        N,M = M,N

    grid = [[0]*M for _ in range(N)]
    free = [list(range(M)) for _ in range(N)]
    sizes = {}
    seen = {}

    for r,c,p in reversed(earthquakes):
        if p == 0:
            continue
        if p <= seen.get((r,c), -1):
            continue
        seen[r,c] = p
        if flip:
            r,c = c,r

        p2 = p*p
        if p not in sizes:
            sizes[p] = [isqrt(p2-d*d) for d in range(-p,p+1)]

        for row,width in enumerate(sizes[p], r-p):
            cols = free[row]
            if not cols:
                continue

            start = bisect_left(cols, c-width)
            if start == len(cols) or cols[start] > c+width:
                continue

            end = bisect_right(cols, c+width, start)
            base = p2-(row-r)**2+1
            for col in cols[start:end]:
                grid[row][col] = base-(col-c)**2
            del cols[start:end]

    if flip:
        return list(map(list, zip(*grid)))
    return grid

def main():
    input = sys.stdin.buffer.readline
    T = int(input())
    for _ in range(T):
        N,M,Q = map(int, input().split())
        earthquakes = []
        for _ in range(Q):
            r,c,p = map(int, input().split())
            earthquakes.append((r,c,p))

        for row in solve(N,M,Q, earthquakes):
            print(" ".join(map(str, row)))

if __name__ == "__main__":
    main()