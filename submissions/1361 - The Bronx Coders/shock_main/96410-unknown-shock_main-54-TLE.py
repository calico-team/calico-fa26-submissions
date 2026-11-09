import sys


def main():
    data = sys.stdin.buffer.read().split()
    t = int(data[0])
    pos = 1
    out = []
    for _ in range(t):
        n, m, q = int(data[pos]), int(data[pos + 1]), int(data[pos + 2])
        pos += 3
        grid = [[0] * m for _ in range(n)]
        for _ in range(q):
            r0, c0, p = int(data[pos]), int(data[pos + 1]), int(data[pos + 2])
            pos += 3
            for r in range(r0 - p, r0 + p + 1):
                row = grid[r]
                dr2 = (r - r0) * (r - r0)
                for c in range(c0 - p, c0 + p + 1):
                    v = p * p - dr2 - (c - c0) * (c - c0) + 1
                    if v > 0:
                        row[c] = v
        for row in grid:
            out.append(" ".join(map(str, row)))
    sys.stdout.write("\n".join(out) + "\n")


main()
