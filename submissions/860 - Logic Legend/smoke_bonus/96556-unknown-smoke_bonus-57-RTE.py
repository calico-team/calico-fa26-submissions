# Source: https://usaco.guide/general/io
import sys

def solve(N, R, A):
    c = 2
    ready = 0
    for t in A:
        while c < 2 and ready <= t:
            c += 1
            ready += R
        if c == 0:
            return "NO"
        if c == 2:
            ready = t + R
        c -= 1
    return "YES"

def main():
    raw = sys.stdin.read()
    if not raw.strip():
        print("No stdin received, using built-in sample", file=sys.stderr)
        raw = """5
5 10
20 30 40 50 60
7 100
1 2 3 4 5 6 7
4 10
1 2 12 13
8 5
5 10 17 30 36 45 50 56
9 30
20 70 80 90 100 190 210 220 250"""
    data = raw.split()
    idx = 0
    T = int(data[idx]); idx += 1
    out = []
    for _ in range(T):
        N = int(data[idx]); R = int(data[idx + 1]); idx += 2
        A = list(map(int, data[idx:idx + N])); idx += N
        out.append(solve(N, R, A))
    print("\n".join(out))

main()