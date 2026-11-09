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


def find(parent, x):
    root = x

    while parent[root] != root:
        root = parent[root]

    while parent[x] != x:
        nxt = parent[x]
        parent[x] = root
        x = nxt

    return root


def solve(N, M, Q, earthquakes):
    answer = [[0] * M for _ in range(N)]

    stride = M + 1
    parent = array('i', range(N * stride))

    for  y, x, p in reversed(earthquakes):
        p2 = p * p

        for r in range(y - p, y + p + 1):
            dy = r - y
            dx = isqrt(p2 - dy * dy)

            base = r * stride
            idx = find(parent, base + x - dx)
            end = base + x + dx

            while idx <= end:
                c = idx - base
                dc = c - x

                answer[r][c] = p2 - dy * dy - dc * dc + 1

                parent[idx] = find(parent, idx + 1)
                idx = parent[idx]

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