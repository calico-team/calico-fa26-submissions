import sys

sys.setrecursionlimit(10000)

# When a level has very many distinct flexible interval types, trying every
# possible "which interval flips" choice is too slow. In that case we only
# branch over a set of representative types (plus the all-0 / all-1 choices).
BRANCH_LIMIT = 48

# Hard cap on the per-test-case memo table. The memo is rebuilt for every
# test case and dropped afterwards; without a cap (and with one table shared
# by all cases) it grows by megabytes per case on files with many medium
# cases and the process runs out of memory.
CACHE_LIMIT = 20000


def _candidates(flex, b, need):
    """Yield candidate reduced-interval lists for the flexible intervals,
    restricted to assignments whose bit-b parity equals `need`.
    flex: list of (l, r) with l < 2^b <= r (bit b flexible)."""
    low_full = (1 << b) - 1
    red0 = [(l, low_full) for (l, r) in flex]          # choose bit b = 0
    red1 = [(0, r - (1 << b)) for (l, r) in flex]      # choose bit b = 1
    nf = len(flex)

    # group identical types
    types = {}
    for i, lr in enumerate(flex):
        types.setdefault(lr, []).append(i)
    type_list = list(types.keys())

    def build(ones):
        ones = set(ones)
        return [red1[i] if i in ones else red0[i] for i in range(nf)]

    seen = set()

    def emit(ones):
        key = tuple(sorted(ones))
        if key not in seen:
            seen.add(key)
            return build(ones)
        return None

    # all zeros (parity 0)
    if need == 0:
        yield emit(())
    # single flips (parity 1)
    if need == 1:
        reps = type_list
        limit = BRANCH_LIMIT if nf <= 20000 else 10
        if len(reps) > limit:
            # representatives: extremes that are most likely to matter
            reps = sorted(
                reps,
                key=lambda lr: (-(lr[1] - (1 << b)), lr[0]),
            )[:limit]
        for lr in reps:
            yield emit((types[lr][0],))
    # pair flips (parity 0)
    if need == 0 and nf >= 2:
        reps = type_list
        if len(reps) > 6:
            reps = sorted(
                reps,
                key=lambda lr: (-(lr[1] - (1 << b)), lr[0]),
            )[:6]
        for a in range(len(reps)):
            for c in range(a, len(reps)):
                ta, tc = reps[a], reps[c]
                if ta == tc:
                    if len(types[ta]) >= 2:
                        yield emit((types[ta][0], types[ta][1]))
                else:
                    yield emit((types[ta][0], types[tc][0]))
    # all ones (parity = nf mod 2)
    if nf % 2 == need and nf > 2:
        yield emit(tuple(range(nf)))


def max_xor(intervals, b, cache):
    """intervals: tuple of (l, r), all with 0 <= l <= r < 2^(b+1).
    Returns the maximum XOR of one choice per interval, over bits <= b.
    `cache` is a memo dict owned by the current test case."""
    if b < 0 or not intervals:
        return 0
    if len(intervals) <= 64 and len(cache) < CACHE_LIMIT:
        key = (intervals, b)
        hit = cache.get(key)
        if hit is not None:
            return hit
        val = _compute(intervals, b, cache)
        cache[key] = val
        return val
    return _compute(intervals, b, cache)


def _compute(intervals, b, cache):
    full = (1 << (b + 1)) - 1
    if len(intervals) == 1:
        return intervals[0][1]
    mask = (1 << b) - 1
    fixed = []
    flex = []
    fa = fixed.append
    xa = flex.append
    parity = 0
    for (l, r) in intervals:
        if l == 0 and r == full:
            return full  # a totally free variable absorbs any target
        hb = l >> b
        if hb == (r >> b):
            parity ^= hb & 1
            fa((l & mask, r & mask))
        else:
            xa((l, r))
    if not flex:
        return (parity << b) | max_xor(tuple(fixed), b - 1, cache)
    need = 1 ^ parity  # flex parity required for answer bit b = 1
    best = -1
    for cand in _candidates(flex, b, need):
        if cand is None:
            continue
        val = (1 << b) | max_xor(tuple(fixed + cand), b - 1, cache)
        if val > best:
            best = val
            if best == full:
                return full
    return best


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    it = iter(data)
    t = next(it, 0)
    out = []
    for _ in range(t):
        n = next(it)
        L = [next(it) for _ in range(n)]
        R = [next(it) for _ in range(n)]
        intervals = tuple(zip(L, R))
        cache = {}  # fresh memo for this case only; freed when the case ends
        out.append(str(max_xor(intervals, 29, cache)))
    sys.stdout.write("\n".join(out))


if __name__ == "__main__":
    solve()
