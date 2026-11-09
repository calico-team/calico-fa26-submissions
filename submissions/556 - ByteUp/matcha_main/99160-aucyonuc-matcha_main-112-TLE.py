
import sys


def blocks(l, r):
    while l <= r:
        if l == 0:
            size = 1 << (r.bit_length() - 1) if r else 1
        else:
            size = l & -l

        while size > r - l + 1:
            size >>= 1

        yield (l, size)
        l += size


def normalize(items):
    items.sort()
    merged = []

    for a, size in items:
        end = a + size - 1

        if merged and a <= merged[-1][1] + 1:
            if end > merged[-1][1]:
                merged[-1] = (merged[-1][0], end)
        else:
            merged.append((a, end))

    result = []
    for l, r in merged:
        result.extend(blocks(l, r))

    return result


def solve(N: int, L: list[int], R: list[int]) -> int:
    fixed_xor = 0
    intervals = []

    for l, r in zip(L, R):
        if l == r:
            fixed_xor ^= l
        else:
            intervals.append((l, r))

    if not intervals:
        return fixed_xor

    intervals.sort(key=lambda p: p[1] - p[0], reverse=True)

    current = [(0, 1)]
    FULL = 1 << 30

    for l, r in intervals:
        choices = list(blocks(l, r))
        next_blocks = []

        for a, sa in current:
            for b, sb in choices:
                size = max(sa, sb)
                base = (a ^ b) & -size
                next_blocks.append((base, size))

        current = normalize(next_blocks)

        if len(current) == 1 and current[0] == (0, FULL):
            return FULL - 1

    answer = 0

    for base, size in current:
        value = ((base ^ fixed_xor) & -size) + size - 1
        if value > answer:
            answer = value

    return answer


def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    it = iter(data)

    T = next(it)
    answers = []

    for _ in range(T):
        N = next(it)
        L = [next(it) for _ in range(N)]
        R = [next(it) for _ in range(N)]

        answers.append(str(solve(N, L, R)))

    sys.stdout.write("\n".join(answers))


if __name__ == "__main__":
    main()
