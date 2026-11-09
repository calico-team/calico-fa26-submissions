
import sys
from functools import lru_cache

def solve(N, L, R):
    if N == 1:
        return R[0]

    base = 0
    for x in L:
        base ^= x

    B = max((a ^ b).bit_length() for a, b in zip(L, R))
    if B == 0:
        return base

    mask = (1 << B) - 1
    target = (base ^ mask) & mask
    intervals = []
    basis = [0] * B

    for a, b in zip(L, R):
        if a == b:
            continue
        if b == a + 1:
            v = a ^ b
            while v:
                p = v.bit_length() - 1
                if basis[p]:
                    v ^= basis[p]
                else:
                    basis[p] = v
                    break
        else:
            intervals.append((a & mask, b & mask))

    for p in range(B):
        if basis[p]:
            for q in range(p + 1, B):
                if basis[q] >> p & 1:
                    basis[q] ^= basis[p]

    states = {(0, tuple(x for x in basis if x))}
    intervals.sort(key=lambda x: x[1] - x[0], reverse=True)

    @lru_cache(None)
    def reduce(x, b):
        for v in reversed(b):
            if x >> (v.bit_length() - 1) & 1:
                x ^= v
        return x

    @lru_cache(None)
    def extend(b, v):
        d = [0] * B
        for x in b:
            d[x.bit_length() - 1] = x

        while v:
            p = v.bit_length() - 1
            if d[p]:
                v ^= d[p]
            else:
                d[p] = v
                break

        for p in range(B):
            if d[p]:
                for q in range(p + 1, B):
                    if d[q] >> p & 1:
                        d[q] ^= d[p]

        return tuple(x for x in d if x)

    @lru_cache(None)
    def add_low(b, k):
        d = [0] * B
        for p in range(k):
            d[p] = 1 << p

        for v in b:
            v = (v >> k) << k
            while v:
                p = v.bit_length() - 1
                if d[p]:
                    v ^= d[p]
                else:
                    d[p] = v
                    break

        for p in range(B):
            if d[p]:
                for q in range(p + 1, B):
                    if d[q] >> p & 1:
                        d[q] ^= d[p]

        return tuple(x for x in d if x)

    def simplify(states):
        while True:
            groups = {}
            for o, b in states:
                groups.setdefault(b, []).append(o)

            changed = False
            for b, offsets in groups.items():
                if len(offsets) > 1:
                    x, y = offsets[:2]
                    states.remove((x, b))
                    states.remove((y, b))
                    nb = extend(b, x ^ y)
                    states.add((reduce(x, nb), nb))
                    changed = True
                    break

            if not changed:
                break

        if len(states) == 1:
            return states

        items = list(states)
        keep = set(items)

        for o, b in items:
            for u, c in items:
                if (o, b) == (u, c) or len(b) > len(c):
                    continue
                if reduce(o ^ u, c):
                    continue
                if all(reduce(v, c) == 0 for v in b):
                    keep.discard((o, b))
                    break

        return keep

    for lo, hi in intervals:
        blocks = []
        cur = lo

        while cur <= hi:
            if cur:
                size = cur & -cur
            else:
                size = 1 << ((hi - cur + 1).bit_length() - 1)

            while size > hi - cur + 1:
                size >>= 1

            blocks.append((cur ^ lo, size.bit_length() - 1))
            cur += size

        nxt = set()

        for o, b in states:
            for v, k in blocks:
                nb = add_low(b, k)
                nxt.add((reduce(o ^ v, nb), nb))

        states = simplify(nxt)

        for o, b in states:
            if reduce(target ^ o, b) == 0:
                return base & ~mask | mask

    ans = 0
    for o, b in states:
        x = (base & mask) ^ o
        for v in reversed(b):
            if (x ^ v) > x:
                x ^= v
        ans = max(ans, x)

    return (base & ~mask) | ans


def main():
    data = iter(map(int, sys.stdin.buffer.read().split()))
    T = next(data)
    out = []

    for _ in range(T):
        N = next(data)
        L = [next(data) for _ in range(N)]
        R = [next(data) for _ in range(N)]
        out.append(str(solve(N, L, R)))

    sys.stdout.write('\n'.join(out) + '\n')


if __name__ == '__main__':
    main()
