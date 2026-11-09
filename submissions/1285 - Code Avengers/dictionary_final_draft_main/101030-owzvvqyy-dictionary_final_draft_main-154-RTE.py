
def solve(N: int, A: list, V: list) -> list:
    """
    Return an array of N integers, the i-th of which
    represents Big Ben's maximum happiness if he
    starts by trying to define word i.

    N: the number of words in the dictionary
    A: the first word in the definition of word i
    V: the value associated with the happiness of each word
    """

    nxt = [a - 1 for a in A]
    seen = [0] * N
    onCycle = [False] * N
    loops = []
    for s in range(N):
        if seen[s]:
            continue
        trail = []
        u = s
        while seen[u] == 0:
            seen[u] = 1
            trail.append(u)
            u = nxt[u]
        if seen[u] == 1:
            ring = [u]
            onCycle[u] = True
            w = nxt[u]
            while w != u:
                ring.append(w)
                onCycle[w] = True
                w = nxt[w]
            loops.append(ring)
        for p in trail:
            seen[p] = 2
    kids = [[] for _ in range(N)]
    for u in range(N):
        if not onCycle[u]:
            kids[nxt[u]].append(u)

    zero = [0]
    one = [0]
    cnt = [0]
    bits = [1 << b for b in range(29, -1, -1)]

    def add(t, x, d):
        for m in bits:
            if x & m:
                y = one[t]
                if not y:
                    y = len(cnt)
                    one[t] = y
                    zero.append(0); one.append(0); cnt.append(0)
            else:
                y = zero[t]
                if not y:
                    y = len(cnt)
                    zero[t] = y
                    zero.append(0); one.append(0); cnt.append(0)
            t = y
            cnt[t] += d

    def best(t, x):
        res = 0
        for m in bits:
            if x & m:
                y = zero[t]
                if y and cnt[y]:
                    res |= m
                    t = y
                else:
                    t = one[t]
            else:
                y = one[t]
                if y and cnt[y]:
                    res |= m
                    t = y
                else:
                    t = zero[t]
        return res

    def fresh():
        zero.append(0); one.append(0); cnt.append(0)
        return len(cnt) - 1

    out = [0] * N
    depthXor = [0] * N
    for ring in loops:
        del zero[1:]
        del one[1:]
        del cnt[1:]
        L = len(ring)
        pref = [0] * L
        acc = 0
        for j in range(L):
            acc ^= V[ring[j]]
            pref[j] = acc
        total = acc
        ringTrie = fresh()
        for x in pref:
            add(ringTrie, x, 1)
        pathTrie = fresh()
        add(pathTrie, 0, 1)
        for k in range(L):
            r = ring[k]
            shift = pref[k - 1] if k else 0
            a1 = best(ringTrie, shift)
            a2 = best(ringTrie, shift ^ total)
            out[r] = a1 if a1 > a2 else a2
            stack = kids[r][:]
            while stack:
                u = stack.pop()
                if u < 0:
                    add(pathTrie, depthXor[~u], -1)
                    continue
                qu = V[u] ^ depthXor[nxt[u]]
                depthXor[u] = qu
                key = qu ^ shift
                a1 = best(pathTrie, qu)
                a2 = best(ringTrie, key)
                a3 = best(ringTrie, key ^ total)
                if a2 > a1:
                    a1 = a2
                out[u] = a1 if a1 > a3 else a3
                add(pathTrie, qu, 1)
                stack.append(~u)
                stack.extend(kids[u])
    return out

def tokens():
    while True:
        try:
            line = input()
        except EOFError:
            return
        for x in line.split():
            yield x

def main():
    it = tokens()
    T = int(next(it))
    for _ in range(T):
        N = int(next(it))
        A = [int(next(it)) for _ in range(N)]
        V = [int(next(it)) for _ in range(N)]
        print(' '.join(map(str, solve(N, A, V))))

if __name__ == '__main__':
    main()