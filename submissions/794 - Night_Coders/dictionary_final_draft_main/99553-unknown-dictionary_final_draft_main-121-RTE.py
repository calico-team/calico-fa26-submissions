from __future__ import annotations

try:
    import numpy as np
    HAVE_NP = True
except ImportError:
    HAVE_NP = False

BITS = 30


def _structure(N, f, V):
    state = [0] * N            # yahan pe hum blkul hi 0 se shur krtya hue backward jayein gy
    cyc = [-1] * N             # cycle ids bnaye gy jo k cycle nodes ko show kryn ghi
    pos = [0] * N
    cycles = []                # node ki list aik order ko follow krty hur agay brhyn ghi
    for s in range(N):
        if state[s]:
            continue
        path = []
        x = s
        while state[x] == 0:
            state[x] = 1
            path.append(x)
            x = f[x]
        if state[x] == 1:      # jaisy hi koi cycle found hoga yeh us ko x se start kr dy ga
            k = path.index(x)
            nodes = path[k:]
            cid = len(cycles)
            for j, y in enumerate(nodes):
                cyc[y] = cid
                pos[y] = j
            cycles.append(nodes)
        for y in path:
            state[y] = 2

    # hum yhn pr W and entry ko processing nodes k tour pe rkhyn gy ta k sof(x) pehllay finsh ho sky
    W = [0] * N
    entry = list(range(N))
    done = [c >= 0 for c in cyc]
    for s in range(N):
        if done[s]:
            continue
        stack = []
        x = s
        while not done[x]:
            stack.append(x)
            x = f[x]
        while stack:
            y = stack.pop()
            W[y] = V[y] ^ W[f[y]]
            entry[y] = entry[f[y]]
            done[y] = True

    #forest ka DFS order jo wo hoga
    children = [[] for _ in range(N)]
    for x in range(N):
        if cyc[x] < 0:
            children[f[x]].append(x)
    tin = [0] * N
    tout = [0] * N
    t = 0
    for r in range(N):
        if cyc[r] < 0:
            continue
        stack = [(r, 0)]
        tin[r] = t; t += 1
        while stack:
            x, i = stack[-1]
            ch = children[x]
            if i < len(ch):
                stack[-1] = (x, i + 1)
                y = ch[i]
                tin[y] = t; t += 1
                stack.append((y, 0))
            else:
                tout[x] = t
                stack.pop()

    # hum yhn pr na honay wali surt hal ko janchna pry ga
    P = [0] * N                # p inclusively cycle node ko analyze kry ga
    U = []                     
    for cid, nodes in enumerate(cycles):
        acc = 0
        for y in nodes:
            acc ^= V[y]
            P[y] = acc
        S = acc
        for y in nodes:
            U.append((cid, P[y]))
            U.append((cid, P[y] ^ S))
    #abb hum hr key ko hr node k lie run kr k result lyn gy
    ckey = [0] * N
    ccid = [0] * N
    for i in range(N):
        e = entry[i]
        cid = cyc[e]
        a = pos[e]
        prev = cycles[cid][a - 1] if a > 0 else -1
        ckey[i] = W[i] ^ (P[prev] if prev >= 0 else 0)
        ccid[i] = cid
    return cyc, W, tin, tout, U, ckey, ccid


def _solve_numpy(N, f, V):
    cyc, W, tin, tout, U, ckey, ccid = _structure(N, f, V)
    W = np.array(W, dtype=np.int64)
    tin = np.array(tin, dtype=np.int64)
    tout = np.array(tout, dtype=np.int64)
    BIG = N + 1

    #cycle part yhn pr over honay k chances rkhta hai
    Uarr = np.array(U, dtype=np.int64).reshape(-1, 2)
    comb = np.sort(Uarr[:, 0] * (1 << BITS) + Uarr[:, 1])      #br br adlabadli is ko durust kry ga
    key = np.array(ckey, dtype=np.int64)
    cid = np.array(ccid, dtype=np.int64)
    up = np.zeros(N, dtype=np.int64)
    for s in range(BITS - 1, -1, -1):
        kb = (key >> s) & 1
        t = up * 2 + (1 - kb)
        cls = comb >> s
        q = (cid << (BITS - s)) + t
        j = np.searchsorted(cls, q)
        ex = (j < cls.size) & (cls[np.minimum(j, cls.size - 1)] == q)
        up = np.where(ex, t, up * 2 + kb)
    best = key ^ up

    #taile part ko zara aik sequence main chalayein gy
    tail = np.nonzero(np.array(cyc) < 0)[0]
    if tail.size:
        farr = np.array(f, dtype=np.int64)
        qkey = W[tail]
        qx = tin[farr[tail]]
        up = np.zeros(tail.size, dtype=np.int64)
        for s in range(BITS - 1, -1, -1):
            cls = W >> s
            sk = cls * BIG + tin
            order = np.argsort(sk)          # keys hamray pass unique hain
            sk = sk[order]
            ek = (cls * BIG + tout)[order]
            pm = np.maximum.accumulate(ek)
            keep = np.empty(ek.size, dtype=bool)
            keep[0] = True
            keep[1:] = ek[1:] > pm[:-1]              #yhn pr outermost keys ayein ghi
            ms = sk[keep]; me = ek[keep]
            kb = (qkey >> s) & 1
            t = up * 2 + (1 - kb)
            q = t * BIG + qx
            j = np.searchsorted(ms, q, side='right') - 1
            ex = (j >= 0) & (me[np.maximum(j, 0)] > q)
            up = np.where(ex, t, up * 2 + kb)
        best[tail] = np.maximum(best[tail], qkey ^ up)
    return best.tolist()


def _solve_python(N, f, V):
    """Fallback without numpy: persistent binary tries."""
    cyc, W, tin, tout, U, ckey, ccid = _structure(N, f, V)
    L = [0]; R = [0]           # node 0 = empty trie

    def insert(root, val):
        new_root = len(L)
        L.append(L[root]); R.append(R[root])
        cur, old = new_root, root
        for s in range(BITS - 1, -1, -1):
            nxt = len(L)
            if (val >> s) & 1:
                o = R[old]; L.append(L[o]); R.append(R[o]); R[cur] = nxt
            else:
                o = L[old]; L.append(L[o]); R.append(R[o]); L[cur] = nxt
            cur, old = nxt, o
        return new_root

    def query(root, key):
        cur = root; res = 0
        for s in range(BITS - 1, -1, -1):
            b = (key >> s) & 1
            if b:
                if L[cur]: cur = L[cur]; res |= 1 << s
                else: cur = R[cur]
            else:
                if R[cur]: cur = R[cur]; res |= 1 << s
                else: cur = L[cur]
        return res

    croot = {}
    for c, val in U:
        croot[c] = insert(croot.get(c, 0), val)
    best = [query(croot[ccid[i]], ckey[i]) for i in range(N)]
    # Tail tries along the forest, built parent-first (BFS order by tin)
    troot = [0] * N
    for x in sorted(range(N), key=tin.__getitem__):
        troot[x] = insert(troot[f[x]] if cyc[x] < 0 else 0, W[x] if cyc[x] < 0 else 0)
    for i in range(N):
        if cyc[i] < 0:
            v = query(troot[f[i]], W[i])
            if v > best[i]:
                best[i] = v
    return best


def solve(N: int, A: list[int], V: list[int]) -> list[int]:
    #bhai sahib saray functions ready hain so time to run them, getting ready them for the main function
    f = [a - 1 for a in A]
    if HAVE_NP:
        return _solve_numpy(N, f, V)
    return _solve_python(N, f, V)

def main():
    T = int(input())
    for _ in range(T):
        N = int(input())
        A = list(map(int, input().split()))
        V = list(map(int, input().split()))
        print(' '.join(map(str, solve(N, A, V))))

if __name__ == '__main__':
    main()