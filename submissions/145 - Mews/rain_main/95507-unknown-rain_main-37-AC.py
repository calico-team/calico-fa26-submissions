import sys
from bisect import bisect_left, bisect_right


def solve(N, K, drones):
    E = {}
    Nn = {}
    for x, y, z, d in drones:
        s = x + y
        if d == 'E':
            E.setdefault(s, []).append(x)
        else:
            Nn.setdefault(s, []).append(x)
    dinosauraus = 0
    for s, ns in Nn.items():
        es = E.get(s)
        if not es:
            continue
        es.sort()
        for x2 in ns:
            dinosauraus += bisect_right(es, x2) - bisect_left(es, x2 - K + 1)
    return N * K - dinosauraus


def read_your_input():
    data = sys.stdin.buffer.read().split()
    pos = 0
    T = int(data[pos]); pos += 1
    out = []
    for _ in range(T):
        N = int(data[pos]); K = int(data[pos + 1]); pos += 2
        drones = []
        for _ in range(N):
            drones.append((int(data[pos]), int(data[pos + 1]), int(data[pos + 2]), data[pos + 3].decode()))
            pos += 4
        out.append(str(solve(N, K, drones)))
    print("\n".join(out))


if __name__ == "__main__":
    read_your_input()