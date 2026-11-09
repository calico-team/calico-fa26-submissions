import sys
from bisect import bisect_left, bisect_right


def main():
    data = sys.stdin.read().split()
    pos = 0
    t = int(data[pos])
    pos += 1
    out = []
    for _ in range(t):
        n = int(data[pos])
        k = int(data[pos + 1])
        pos += 2
        E = {}
        Nn = {}
        for _ in range(n):
            x = int(data[pos])
            y = int(data[pos + 1])
            d = data[pos + 3]
            pos += 4
            s = x + y
            if d == "E":
                E.setdefault(s, []).append(x)
            else:
                Nn.setdefault(s, []).append(x)
        pairs = 0
        for s, nl in Nn.items():
            el = E.get(s)
            if not el:
                continue
            el.sort()
            for xj in nl:

                pairs += bisect_right(el, xj) - bisect_left(el, xj - k + 1)
        out.append(str(n * k - pairs))
    print("\n".join(out))


main()
