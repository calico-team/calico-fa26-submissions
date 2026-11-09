from itertools import combinations
def solve(N: int, L: list[int], R: list[int]) -> int:
    """
    Returns the maximum possible value of X, Big Ben's matcha enjoyment.

    N: the days in Big Ben's life
    L: the lower bound of enjoyment from each store 
    R: the upper bound of enjoyment from each store
    """
    def insert(basis, v):
        while v:
            p = v.bit_length() - 1
            if basis[p]:
                v ^= basis[p]
            else:
                basis[p] = v
                return True
        return False
    
    def in_span(basis, v):
        while v:
            p = v.bit_length() - 1
            if not basis[p]:
                return False
            v ^= basis[p]
        return True
    
    base = 0
    for x in L:
        base ^= x
    diffs = [l ^ r for l, r in zip(L, R)]
    basis = [0] * 31
    for d in set(diffs):
        insert(basis, d)
    best = base
    for v in sorted(filter(None, basis), reverse=True):
        if best ^ v > best:
            best ^= v
    
    by_top = {}
    for i, d in enumerate(diffs):
        if d:
            by_top.setdefault(d.bit_length() - 1, []).append(i)
    if not by_top:
        return best
    
    def level_feasible(B, above):
        cand = []
        stuck = set()
        for i in above:
            lo_ok = not (L[i] >> B) & 1
            hi_ok = (R[i] >> B) & 1
            if lo_ok or hi_ok:
                cand.append((diffs[i] >> B, None if lo_ok and hi_ok else (0 if lo_ok else 1)))
            else:
                stuck.add(diffs[i] >> B)
        if not cand:
            return False, False
        free_basis = [0] * 31
        for v in stuck:
            insert(free_basis, v)
        if B in by_top:
            insert(free_basis, 1)
        full = free_basis[:]
        spare = 0
        for v in {v for v, _ in cand}:
            if not insert(full, v):
                spare += 1
        spare += len(cand) - len({v for v, _ in cand})
    
        def ok(tau):
            goal = (best >> (B + 1)) << 1 | tau
            for toggles in (1, 2):
                target = goal ^ (base >> B) ^ (toggles & 1)
                if not in_span(full, target):
                    continue
                if spare >= toggles:
                    return True
                for chosen in combinations(range(len(cand)), toggles):
                    pinned = [idx for idx in chosen if cand[idx][1] is not None]
                    fixed = 0
                    for idx in pinned:
                        if cand[idx][1]:
                            fixed ^= cand[idx][0]
                    rest = free_basis[:]
                    for idx, (v, _) in enumerate(cand):
                        if idx not in pinned:
                            insert(rest, v)
                    if in_span(rest, target ^ fixed):
                        return True
            return False
    
        if ok(1):
            return True, True
        return False, not (best >> B) & 1 and ok(0)
    
    top = max(by_top)
    above = list(by_top[top])
    for B in range(top - 1, -1, -1):
        one, zero = level_feasible(B, above)
        if one:
            return best | ((1 << (B + 1)) - 1)
        if zero:
            return best | ((1 << B) - 1)
        above.extend(by_top.get(B, ()))
    return best

def main():
    T = int(input())
    for _ in range(T):
        N = int(input())
        L = list(map(int, input().split()))
        R = list(map(int, input().split()))
        print(solve(N, L, R))

if __name__ == '__main__':
    main()
