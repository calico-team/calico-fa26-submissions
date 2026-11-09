
import sys

BITS = 30
MASK = (1 << BITS) - 1


def best_in_range(x, l, r):
    prefix = 0

    for b in range(BITS - 1, -1, -1):
        bit = 1 << b
        xb = (x >> b) & 1

        # Try to make the XOR bit 1
        candidate = prefix | ((1 - xb) << b)
        low = candidate << b
        high = low + bit - 1

        if high >= l and low <= r:
            prefix = candidate
        else:
            prefix |= xb << b

    return prefix


def optimize(L, R, initial, reverse=False):
    n = len(L)
    values = initial[:]
    current = 0

    for v in values:
        current ^= v

    order = range(n - 1, -1, -1) if reverse else range(n)

    for i in order:
        current ^= values[i]
        values[i] = best_in_range(current, L[i], R[i])
        current ^= values[i]

    return current


def solve():
    data = iter(map(int, sys.stdin.buffer.read().split()))
    T = next(data)
    results = []

    for _ in range(T):
        n = next(data)
        L = [next(data) for _ in range(n)]
        R = [next(data) for _ in range(n)]

        candidates = [
            optimize(L, R, L),
            optimize(L, R, R, True),
        ]

        results.append(str(max(candidates)))

    print("\n".join(results))


if __name__ == "__main__":
    solve()
