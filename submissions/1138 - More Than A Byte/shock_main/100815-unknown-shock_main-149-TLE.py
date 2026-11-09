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
from array import array


def solve(N, M, Q, earthquakes):
    answer = [[0] * M for _ in range(N)]

    stride = M + 1
    parent = array('i', range(N * stride))
    radiusCache = {}

    for y, x, p in reversed(earthquakes):
        if p not in radiusCache:
            p2 = p * p
            radiusCache[p] = [
                isqrt(p2 - d * d) for d in range(-p, p + 1)
            ]

        radii = radiusCache[p]
        p2 = p * p

        for i, dx in enumerate(radii):
            r = y - p + i
            dy = r - y
            base = r * stride

            idx = base + x - dx

            while parent[idx] != idx:
                parent[idx] = parent[parent[idx]]
                idx = parent[idx]

            end = base + x + dx
            vertical = p2 - dy * dy + 1

            while idx <= end:
                c = idx - base
                dc = c - x

                answer[r][c] = vertical - dc * dc

                nxt = idx + 1

                while parent[nxt] != nxt:
                    parent[nxt] = parent[parent[nxt]]
                    nxt = parent[nxt]

                parent[idx] = nxt
                idx = nxt

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