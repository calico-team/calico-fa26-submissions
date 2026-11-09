
import sys

def blocks(l, r):
    res = []
    while l <= r:
        if l == 0:
            k = 30
        else:
            k = (l & -l).bit_length() - 1

        while (1 << k) > r - l + 1:
            k -= 1

        res.append((l, k))
        l += 1 << k

    return res


def solve():
    data = iter(map(int, sys.stdin.buffer.read().split()))
    t = next(data)
    out = []

    for _ in range(t):
        n = next(data)
        L = [next(data) for _ in range(n)]
        R = [next(data) for _ in range(n)]

        cur = [(0, 0)]

        for i in range(n):
            d = blocks(L[i], R[i])
            nxt = set()

            for s, k in cur:
                for v, j in d:
                    z = max(k, j)
                    start = ((s >> z) ^ (v >> z)) << z
                    nxt.add((start, z))

            cur = list(nxt)

        ans = max(s + (1 << k) - 1 for s, k in cur)
        out.append(str(ans))

    sys.stdout.write("\n".join(out))


if __name__ == "__main__":
    solve()
