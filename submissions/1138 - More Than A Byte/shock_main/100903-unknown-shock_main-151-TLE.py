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


def solve(N, M, Q, earthquakes):
    answer = [[0] * M for _ in range(N)]
    rowMasks = [(1 << M) - 1] * N
    radiusCache = {}

    for y, x, p in reversed(earthquakes):
        if p not in radiusCache:
            p2 = p * p
            radiusCache[p] = [
                isqrt(p2 - d * d) for d in range(-p, p + 1)
            ]

        p2 = p * p
        radii = radiusCache[p]

        for i, dx in enumerate(radii):
            r = y - p + i
            left = x - dx
            width = 2 * dx + 1

            mask = ((1 << width) - 1) << left
            available = rowMasks[r] & mask

            if not available:
                continue

            vertical = p2 - (r - y) ** 2 + 1

            while available:
                bit = available & -available
                available ^= bit
                rowMasks[r] ^= bit

                c = bit.bit_length() - 1
                dc = c - x
                answer[r][c] = vertical - dc * dc

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