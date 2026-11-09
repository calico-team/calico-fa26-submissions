import sys
from math import isqrt

def main():
    data = sys.stdin.buffer.read().split()
    pos_in = 0
    t = int(data[pos_in])
    pos_in += 1
    out = []

    for _ in range(t):
        n = int(data[pos_in])
        m = int(data[pos_in + 1])
        q = int(data[pos_in + 2])
        pos_in += 3

        quakes = []
        for _ in range(q):
            r = int(data[pos_in])
            c = int(data[pos_in + 1])
            p = int(data[pos_in + 2])
            quakes.append((r, c, p))
            pos_in += 3

        total = n * m
        grid = [0] * total
        parent = list(range(total + 1))

        # Latest earthquake wins, so go from last to first.
        for r, c, p in reversed(quakes):
            power = p * p
            for row in range(r - p, r + p + 1):
                d = row - r
                rem = power - d * d
                w = isqrt(rem)
                base = row * m
                left = base + c - w
                right = base + c + w

                # find first unassigned cell at or after left (path halving)
                x = left
                while parent[x] != x:
                    parent[x] = parent[parent[x]]
                    x = parent[x]

                while x <= right:
                    dc = x - base - c
                    grid[x] = rem - dc * dc + 1
                    parent[x] = x + 1

                    nx = x + 1
                    while parent[nx] != nx:
                        parent[nx] = parent[parent[nx]]
                        nx = parent[nx]
                    x = nx

        for i in range(n):
            out.append(" ".join(map(str, grid[i * m:(i + 1) * m])))

    sys.stdout.write("\n".join(out) + "\n")

if __name__ == "__main__":
    main()