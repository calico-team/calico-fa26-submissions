import sys
from bisect import bisect_left, bisect_right
from math import isqrt

def solve(N, M,Q,earthquakes):
    if N < 3 or M < 3:
        grid = [[0] * M for _ in range(N)]
        for row, col, power in earthquakes:
            grid[row][col] = 1
        return grid

    swapped = M> N
    if swapped:
        N,M = M, N

    grid = [[0] *M for _ in range(N)]
    empty = [list(range(M)) for _ in range(N)]
    widths = {}
    strongest = {}

    for r, c, power in reversed(earthquakes):
        if power <=strongest.get((r, c), -1):
            continue
        strongest[r, c] = power
        if swapped:
            r,c = c, r
        square = power * power
        if power not in widths:
            spans = []
            for offset in range(-power, power + 1):
                spans.append(isqrt(square - offset * offset))
            widths[power] = spans

        for row, width in enumerate(widths[power], r - power):
            cols = empty[row]
            if not cols:
                continue
            start = bisect_left(cols, c - width)
            if start == len(cols) or cols[start] > c + width:
                continue
            end = bisect_right(cols, c + width, start)
            base = square - (row - r)**2 + 1
            for col in cols[start:end]:
                grid[row][col] = base - (col - c)**2
            del cols[start:end]

    if swapped:
        return [list(row) for row in zip(*grid)]
    return grid




def main():
    read = sys.stdin.buffer.readline
    T = int(read())
    for _ in range(T):
        N, M, Q = map(int, read().split())
        earthquakes = []
        for _ in range(Q):
            r, c, power = map(int, read().split())
            earthquakes.append((r, c, power))

        for row in solve(N, M, Q, earthquakes):
            print(" ".join(map(str, row)))




if __name__ == "__main__":
    main()