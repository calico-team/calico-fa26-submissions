import sys
from itertools import accumulate, repeat
from operator import add, le, sub


def main():
    rd = sys.stdin.buffer.readline
    t = int(rd())
    out = []
    for _ in range(t):
        n, r = map(int, rd().split())
        a = list(map(int, rd().split()))
        b = list(map(sub, a, range(0, r * n, r)))
        p = accumulate(b, max)
        ok = all(map(le, p, map(add, b[2:], repeat(r))))
        out.append("YES" if ok else "NO")
    sys.stdout.write("\n".join(out) + "\n")


main()
