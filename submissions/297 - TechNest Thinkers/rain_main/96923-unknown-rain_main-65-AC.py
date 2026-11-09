import sys
from bisect import bisect_left as L, bisect_right as R
def main():
    b = sys.stdin.buffer.read().split(); i = 1; out = []
    for _ in range(int(b[0])):
        n, k = int(b[i]), int(b[i+1]); i += 2
        E = {}; N = []
        for _ in range(n):
            x, y = int(b[i]), int(b[i+1])
            if b[i+3] == b'E': E.setdefault(x+y, []).append(x)
            else: N.append((x+y, x))
            i += 4
        for v in E.values(): v.sort()
        lost = sum(R(E[s], x) - L(E[s], x-k+1) for s, x in N if s in E)
        out.append(n*k - lost)
    print("\n".join(map(str, out)))
main()