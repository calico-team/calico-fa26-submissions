import sys
from bisect import bisect_left, bisect_right
from itertools import compress, repeat
from operator import add, lshift, or_, sub, not_


def main():
    rd = sys.stdin.buffer.readline
    t = int(rd())
    out = []
    for _ in range(t):
        n, k = map(int, rd().split())
        tok = b' '.join([rd() for _ in range(n)]).split()
        xs = list(map(int, tok[0::4]))
        keys = list(map(or_, map(lshift, map(add, xs, map(int, tok[1::4])), repeat(18)), xs))
        is_e = list(map(b'E'.__eq__, tok[3::4]))
        is_n = list(map(not_, is_e))
        e = sorted(compress(keys, is_e))
        nk = list(compress(keys, is_n))
        lo = list(map(sub, nk, map(min, compress(xs, is_n), repeat(k - 1))))
        pairs = sum(map(bisect_right, repeat(e), nk)) - sum(map(bisect_left, repeat(e), lo))
        out.append(n * k - pairs)
    sys.stdout.write("\n".join(map(str, out)) + "\n")


main()
