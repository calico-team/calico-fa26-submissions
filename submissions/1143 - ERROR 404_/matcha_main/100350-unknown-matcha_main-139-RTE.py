import sys

def blocks(l, r):
    res = []
    while l <= r:
        k = 30 if l == 0 else (l & -l).bit_length() - 1
        while (1 << k) > r - l + 1:
            k -= 1
        res.append((l, k))
        l += 1 << k
    return res

def solve():
    input = sys.stdin.buffer.readline
    t = int(input())

    for _ in range(t):
        n = int(input())
        L = list(map(int, input().split()))
        R = list(map(int, input().split()))

        cur = [(0, 0)]

        for l, r in zip(L, R):
            d = blocks(l, r)
            nxt = set()

            for s, k in cur:
                for v, j in d:
                    z = max(k, j)
                    start = ((s >> z) ^ (v >> z)) << z
                    nxt.add((start, z))

            cur = list(nxt)

        print(max(s + (1 << k) - 1 for s, k in cur))

if __name__ == "__main__":
    solve()