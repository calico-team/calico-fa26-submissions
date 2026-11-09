import sys
from array import array

BEST = [0] * 2048            # gponmmg tpo make our very best thing here
for _m in range(1, 256):
    for _t in range(8):
        _bc, _bv = 0, -1
        for _c in range(8):
            if (_m >> _c) & 1 and (_c ^ _t) > _bv:
                _bv, _bc = _c ^ _t, _c
        BEST[(_m << 3) | _t] = _bc
B8 = [8 << _c for _c in range(8)]   # bit for child c in the (<< 3) mask


def solve(N: int, A: list[int], V: list[int]) -> list[int]:
    f = [a - 1 for a in A]

    #apllying khan algorithm here
    deg = [0] * N
    for x in f:
        deg[x] += 1
    has_child = [d > 0 for d in deg]
    order = [i for i in range(N) if deg[i] == 0]
    k = 0
    while k < len(order):
        w = f[order[k]]
        k += 1
        deg[w] -= 1
        if deg[w] == 0:
            order.append(w)
    #x axies on the lies

    #now its time for the scond module
    D = [0] * N
    seen = [False] * N
    cycles = []                      
    nodes_needed = 1                  
    for s in range(N):
        if deg[s] == 0 or seen[s]:
            continue
        cyc = []
        x = s
        while not seen[x]:
            seen[x] = True
            cyc.append(x)
            x = f[x]
        q = 0
        for x in cyc:
            D[x] = q
            q ^= V[x]
        S = set()
        for x in cyc:
            S.add(D[x])
            S.add(D[x] ^ q)
        cycles.append((cyc, S))
        nodes_needed += 1 + sum(min(8 ** lv, len(S)) for lv in range(1, 9))
    internal_tree = sum(1 for u in order if has_child[u])
    nodes_needed += 9 * internal_tree

    del seen
    C = array('i', [0]) * (9 * nodes_needed)    #aik hi dafa allocate ho ga baqi sab zero hongy
    BESTl = BEST

    def query(b, d, C=C, BEST=BESTl):
        # max of d ^ z over all z stored in the trie version whose root is at b
        t = (d >> 27) & 7; c = BEST[C[b + 8] | t]; r = c ^ t; b = C[b + c]
        t = (d >> 24) & 7; c = BEST[C[b + 8] | t]; r = (r << 3) | (c ^ t); b = C[b + c]
        t = (d >> 21) & 7; c = BEST[C[b + 8] | t]; r = (r << 3) | (c ^ t); b = C[b + c]
        t = (d >> 18) & 7; c = BEST[C[b + 8] | t]; r = (r << 3) | (c ^ t); b = C[b + c]
        t = (d >> 15) & 7; c = BEST[C[b + 8] | t]; r = (r << 3) | (c ^ t); b = C[b + c]
        t = (d >> 12) & 7; c = BEST[C[b + 8] | t]; r = (r << 3) | (c ^ t); b = C[b + c]
        t = (d >> 9) & 7; c = BEST[C[b + 8] | t]; r = (r << 3) | (c ^ t); b = C[b + c]
        t = (d >> 6) & 7; c = BEST[C[b + 8] | t]; r = (r << 3) | (c ^ t); b = C[b + c]
        t = (d >> 3) & 7; c = BEST[C[b + 8] | t]; r = (r << 3) | (c ^ t); m = C[b + c]
        t = d & 7; c = BEST[m | t]
        return (r << 3) | (c ^ t)

    def insert_copy(bo, d, bc, C=C, B8=B8):
        #persist entries daly jayeing ghi
        c = (d >> 27) & 7; C[bc:bc + 9] = C[bo:bo + 9]; C[bc + 8] |= B8[c]; bo = C[bo + c]; C[bc + c] = bc + 9; bc += 9
        c = (d >> 24) & 7; C[bc:bc + 9] = C[bo:bo + 9]; C[bc + 8] |= B8[c]; bo = C[bo + c]; C[bc + c] = bc + 9; bc += 9
        c = (d >> 21) & 7; C[bc:bc + 9] = C[bo:bo + 9]; C[bc + 8] |= B8[c]; bo = C[bo + c]; C[bc + c] = bc + 9; bc += 9
        c = (d >> 18) & 7; C[bc:bc + 9] = C[bo:bo + 9]; C[bc + 8] |= B8[c]; bo = C[bo + c]; C[bc + c] = bc + 9; bc += 9
        c = (d >> 15) & 7; C[bc:bc + 9] = C[bo:bo + 9]; C[bc + 8] |= B8[c]; bo = C[bo + c]; C[bc + c] = bc + 9; bc += 9
        c = (d >> 12) & 7; C[bc:bc + 9] = C[bo:bo + 9]; C[bc + 8] |= B8[c]; bo = C[bo + c]; C[bc + c] = bc + 9; bc += 9
        c = (d >> 9) & 7; C[bc:bc + 9] = C[bo:bo + 9]; C[bc + 8] |= B8[c]; bo = C[bo + c]; C[bc + c] = bc + 9; bc += 9
        c = (d >> 6) & 7; C[bc:bc + 9] = C[bo:bo + 9]; C[bc + 8] |= B8[c]; bo = C[bo + c]; C[bc + c] = bc + 9; bc += 9
        c = (d >> 3) & 7; C[bc:bc + 9] = C[bo:bo + 9]; C[bc + 8] |= B8[c]; C[bc + c] = C[bo + c] | B8[d & 7]

    def insert_inplace(b, v, nb, C=C, B8=B8):
        #ordinary data yhn pr dakhil hoga
        c = (v >> 27) & 7; ch = C[b + c]
        if not ch: ch = nb; nb += 9; C[b + c] = ch; C[b + 8] |= B8[c]
        b = ch
        c = (v >> 24) & 7; ch = C[b + c]
        if not ch: ch = nb; nb += 9; C[b + c] = ch; C[b + 8] |= B8[c]
        b = ch
        c = (v >> 21) & 7; ch = C[b + c]
        if not ch: ch = nb; nb += 9; C[b + c] = ch; C[b + 8] |= B8[c]
        b = ch
        c = (v >> 18) & 7; ch = C[b + c]
        if not ch: ch = nb; nb += 9; C[b + c] = ch; C[b + 8] |= B8[c]
        b = ch
        c = (v >> 15) & 7; ch = C[b + c]
        if not ch: ch = nb; nb += 9; C[b + c] = ch; C[b + 8] |= B8[c]
        b = ch
        c = (v >> 12) & 7; ch = C[b + c]
        if not ch: ch = nb; nb += 9; C[b + c] = ch; C[b + 8] |= B8[c]
        b = ch
        c = (v >> 9) & 7; ch = C[b + c]
        if not ch: ch = nb; nb += 9; C[b + c] = ch; C[b + 8] |= B8[c]
        b = ch
        c = (v >> 6) & 7; ch = C[b + c]
        if not ch: ch = nb; nb += 9; C[b + c] = ch; C[b + 8] |= B8[c]
        b = ch
        c = (v >> 3) & 7; C[b + 8] |= B8[c]; C[b + c] |= B8[v & 7]
        return nb

    root = [0] * N
    ans = [0] * N
    nb = 9                                      #aglay farig set ko yh n off kryn gy

    #ab thired cycle ki baari hai
    for cyc, S in cycles:
        r = nb
        nb += 9
        for v in S:
            nb = insert_inplace(r, v, nb)
        for x in cyc:
            root[x] = r
            ans[x] = query(r, D[x])

    #4th part main loops chalaya jaye ga
    for i in range(len(order) - 1, -1, -1):
        u = order[i]
        p = f[u]
        d = V[u] ^ D[p]
        D[u] = d
        pr = root[p]
        ans[u] = query(pr, d)
        if has_child[u]:              #hr dafa leaves ko un ki zarort  puri nahi kryn ghy
            root[u] = nb
            insert_copy(pr, d, nb)
            nb += 81

    return ans


def main():
    #dara kuch aik dafa read kry ga ta k ab koi eror nahi aye
    data = list(map(int, sys.stdin.buffer.read().split()))
    pos = 0
    T = data[pos]; pos += 1
    out = []
    for _ in range(T):
        N = data[pos]; pos += 1
        A = data[pos:pos + N]; pos += N
        V = data[pos:pos + N]; pos += N
        out.append(' '.join(map(str, solve(N, A, V))))
    sys.stdout.write('\n'.join(out) + '\n')


if __name__ == '__main__':
    main()