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

from math import isqrt

def find(parent, x):
    while parent[x] != x:
        parent[x] = parent[parent[x]]
        x = parent[x]
    return x

def solve(N, M, Q, earthquakes):
    transposed = N > M

    if transposed:
        h, w = M, N
    else:
        h, w = N, M

    answer = [[0] * w for _ in range(h)]
    rowMasks = [(1 << w) - 1] * h
    rowParent = list(range(h + 1))
    radiusCache = {}

    for x, y, p in reversed(earthquakes):
        if transposed:
            centerRow, centerCol = y, x
        else:
            centerRow, centerCol = x, y

        if p not in radiusCache:
            p2 = p * p
            radiusCache[p] = [
                isqrt(p2 - d * d) for d in range(-p, p + 1)
            ]

        p2 = p * p
        radii = radiusCache[p]

        r = find(rowParent, centerRow - p)
        endRow = centerRow + p

        while r <= endRow:
            dy = r - centerRow
            dx = radii[dy + p]

            left = centerCol - dx
            mask = ((1 << (2 * dx + 1)) - 1) << left

            available = rowMasks[r] & mask

            if available:
                rowMasks[r] ^= available
                vertical = p2 - dy * dy + 1

                while available:
                    bit = available & -available
                    available ^= bit

                    c = bit.bit_length() - 1
                    dc = c - centerCol
                    answer[r][c] = vertical - dc * dc

                if rowMasks[r] == 0:
                    rowParent[r] = find(rowParent, r + 1)

            r = find(rowParent, r + 1)

    if transposed:
        return [
            [answer[r][c] for r in range(h)]
            for c in range(w)
        ]

    return answer



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