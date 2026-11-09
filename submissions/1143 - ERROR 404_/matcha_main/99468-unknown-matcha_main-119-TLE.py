import sys

input = sys.stdin.readline

BITS = 30
LIMIT = 1 << BITS


def decompose(l, r):
    res = []

    while l <= r:
        if l == 0:
            k = BITS
        else:
            k = (l & -l).bit_length() - 1

        while (1 << k) > r - l + 1:
            k -= 1

        res.append((l, k))
        l += 1 << k

    return res


def normalize(blocks):
    if not blocks:
        return []

    intervals = sorted(
        (s, s + (1 << k) - 1)
        for s, k in blocks
    )

    merged = []

    for l, r in intervals:
        if merged and l <= merged[-1][1] + 1:
            if r > merged[-1][1]:
                merged[-1] = (merged[-1][0], r)
        else:
            merged.append((l, r))

    result = []

    for l, r in merged:
        result.extend(decompose(l, r))

    return result


def solve():
    t = int(input())

    for _ in range(t):
        n = int(input())
        L = list(map(int, input().split()))
        R = list(map(int, input().split()))

        blocks = [(0, 0)]

        for i in range(n):
            other = decompose(L[i], R[i])
            new_blocks = []

            for s, k in blocks:
                for v, j in other:
                    z = max(k, j)
                    start = ((s >> z) ^ (v >> z)) << z
                    new_blocks.append((start, z))

            blocks = normalize(new_blocks)

        ans = max(s + (1 << k) - 1 for s, k in blocks)
        print(ans)


if __name__ == "__main__":
    solve()