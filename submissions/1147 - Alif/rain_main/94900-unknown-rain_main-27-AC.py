import sys
from bisect import bisect_left, bisect_right
from collections import defaultdict

def solve(N, K, ds):
    e = defaultdict(list)   # sum -> X's of E drones
    n = defaultdict(list)   # sum -> X's of N drones

    for x, y, z, d in ds:
        if d == 'E':
            e[x + y].append(x)
        else:
            n[x + y].append(x)

    hits = 0
    for s, nxs in n.items():
        if s not in e:
            continue
        exs = sorted(e[s])
        for xn in nxs:
            lo = bisect_left(exs, xn - K + 1)
            hi = bisect_right(exs, xn)
            hits += hi - lo

    return N * K - hits

def main():
    d = sys.stdin.read().split()
    p = 0
    T = int(d[p]); p += 1
    res = []
    for _ in range(T):
        N = int(d[p]); K = int(d[p + 1]); p += 2
        ds = []
        for _ in range(N):
            x = int(d[p]); y = int(d[p + 1]); z = int(d[p + 2]); dd = d[p + 3]
            p += 4
            ds.append((x, y, z, dd))
        res.append(str(solve(N, K, ds)))
    sys.stdout.write("\n".join(res))

if __name__ == "__main__":
    main()