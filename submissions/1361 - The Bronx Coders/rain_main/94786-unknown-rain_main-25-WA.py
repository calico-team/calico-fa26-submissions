import sys
from bisect import bisect_left, bisect_right

def main():
    data = sys.stdin.buffer.read().split()
    t = int(data[0])
    idx = 1
    out = []
    big = 1 << 20
    for _ in range(t):
        n = int(data[idx]); k = int(data[idx + 1]); idx += 2
        east = []
        north = []
        for _ in range(n):
            x = int(data[idx]); y = int(data[idx + 1])
            if data[idx + 3] == b"E":
                east.append((x + y) * big + x)
            else:
                north.append((x + y, x))
            idx += 4
        east.sort()
        lost = 0
        for s, x in north:
            base = s * big
            lo = lo = x - k + 1 < 0
            lost += bisect_right(east, base + x) - bisect_left(east, base + lo)
        out.append(n * k - lost)
    sys.stdout.write("\n".join(map(str, out)) + "\n")

main()