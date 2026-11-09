import sys

BITS = 30


def solve(L, R):
    const = 0
    groups = {}
    for l, r in zip(L, R):
        if l == r:
            const ^= l
            continue
        s = (l ^ r).bit_length() - 1
        const ^= (l >> (s + 1)) << (s + 1)
        full = (1 << s) - 1
        groups.setdefault(s, []).append((r & full, full ^ (l & full)))

    dmask = 0
    chosen = []
    need = []
    for s in sorted(groups, reverse=True):
        members = groups[s]
        want = 1 ^ ((const ^ dmask) >> s & 1)
        if (len(members) - want) & 1:
            dmask ^= (1 << s) - 1
        pairs = []
        ups = 0
        for x, y in members:
            if x >= y:
                pairs.append((x, y))
                ups += 1
            else:
                pairs.append((y, x))
        chosen.append(pairs)
        if ups & 1 != want:
            need.append(len(chosen) - 1)

    cnt = [0] * BITS

    def add(v, sign):
        t = 0
        while v:
            if v & 1:
                cnt[t] += sign
            v >>= 1
            t += 1

    for pairs in chosen:
        for big, small in pairs:
            add(big, 1)

    mask = const ^ dmask
    splits = set(groups)

    def score():
        ans = 0
        for t in range(BITS - 1, -1, -1):
            c = cnt[t]
            hot = (mask >> t & 1) or t in splits
            if c >= 2 or (c >= 1 and hot):
                return ans | ((1 << (t + 1)) - 1)
            if c >= 1 or hot:
                ans |= 1 << t
        return ans

    def swap(pair, sign):
        add(pair[0], -sign)
        add(pair[1], sign)

    picked = {}
    for _ in range(4):
        changed = False
        for g in sorted(need, key=lambda g: len(chosen[g])):
            pairs = chosen[g]
            if any(a == b for a, b in pairs):
                continue
            if g in picked:
                swap(pairs[picked[g]], -1)
            best = -1
            best_i = -1
            seen = set()
            for i, p in enumerate(pairs):
                if p in seen:
                    continue
                seen.add(p)
                swap(p, 1)
                v = score()
                swap(p, -1)
                if v > best:
                    best = v
                    best_i = i
            if picked.get(g) != best_i:
                changed = True
            picked[g] = best_i
            swap(pairs[best_i], 1)
        if not changed:
            break
    return score()


def main():
    data = sys.stdin.buffer.read().split()
    pos = 0
    t = int(data[pos])
    pos += 1
    out = []
    for _ in range(t):
        n = int(data[pos])
        pos += 1
        L = list(map(int, data[pos:pos + n]))
        pos += n
        R = list(map(int, data[pos:pos + n]))
        pos += n
        out.append(solve(L, R))
    print("\n".join(map(str, out)))


main()