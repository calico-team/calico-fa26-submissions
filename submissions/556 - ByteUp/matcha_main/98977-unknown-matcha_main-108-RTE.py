
import sys


def blocks(l, r):
    result = []
    while l <= r:
        if l == 0:
            size = 1 << (r.bit_length() - 1)
        else:
            size = l & -l
        while size > r - l + 1:
            size >>= 1
        result.append((l, size))
        l += size
    return result


def normalize(items):
    present = set()

    for base, size in sorted(items, key=lambda x: -x[1]):
        if any((base & ~(s - 1), s) in present
               for s in (1 << k for k in range(size.bit_length(), 31))):
            continue

        while size < (1 << 30):
            sibling = (base ^ size, size)
            if sibling not in present:
                break
            present.remove(sibling)
            base &= ~(size)
            size <<= 1

        present.add((base, size))

    return list(present)


def solve(N: int, L: list[int], R: list[int]) -> int:
    current = [(0, 1)]

    for l, r in zip(L, R):
        choices = blocks(l, r)
        next_blocks = []

        for a, sa in current:
            for b, sb in choices:
                size = max(sa, sb)
                base = (a ^ b) & ~(size - 1)
                next_blocks.append((base, size))

        current = normalize(next_blocks)

        if len(current) == 1 and current[0] == (0, 1 << 30):
            return (1 << 30) - 1

    return max(base + size - 1 for base, size in current)


def main():
    input = sys.stdin.readline
    T = int(input())

    for _ in range(T):
        N = int(input())
        L = list(map(int, input().split()))
        R = list(map(int, input().split()))
        print(solve(N, L, R))


if __name__ == '__main__':
    main()
