import sys
from bisect import bisect_right
from itertools import compress, repeat


W = 1 << 18          # 262144 > 2e5


def solve(N, K, X, Y, D):
    span = min(K - 1, 100000)
    if span <= 0:                      #koi b drioopp abhi rak move nahi hua hai
        return N * K
    keys = list(map(int.__add__, map(W.__mul__, map(int.__add__, X, Y)), X))
    keyE = sorted(compress(keys, map(b'E'.__eq__, D)))
    keyN = sorted(compress(keys, map(b'N'.__eq__, D)))
    if not keyE or not keyN:
        return N * K
    hi = sum(map(bisect_right, repeat(keyN), map(span.__add__, keyE)))  # keys ki values bari hain
    lo = sum(map(bisect_right, repeat(keyN), keyE))                     # keys ki values choti hain
    return N * K - (hi - lo)


def main():
    data = sys.stdin.buffer.read().split()
    T = int(data[0])
    p = 1
    out = []
    for _ in range(T):
        N = int(data[p]); K = int(data[p + 1]); p += 2
        X = list(map(int, data[p:p + 4 * N:4]))
        Y = list(map(int, data[p + 1:p + 4 * N:4]))
        D = data[p + 3:p + 4 * N:4]            # b'E' / b'N'
        p += 4 * N
        out.append(str(solve(N, K, X, Y, D)))
    sys.stdout.write('\n'.join(out) + '\n')


if __name__ == '__main__':
    main()