import numpy as np


def solve(N, A, V):
    """
    Functional graph i -> A[i]. Happiness after k steps = XOR of V over the first k nodes
    of the walk (k >= 1); answer = max over k.
    Tree nodes: W(u) = V[u] ^ W(parent), W(cycle node) = 0.
      * stopping inside the tree part / at the cycle entry c:  W(i) ^ W(a), a = proper ancestor
        (incl. root c)                                          -> part 1
      * stopping while on the cycle: W(i) ^ (XOR of j cycle nodes starting at c), j >= 1.
        With cycle prefix xors Pre, this is W(i) ^ Pre[s] ^ u for u in the static set
        {Pre[r], Pre[r]^X : r = 1..L} of that cycle (s = position of c)   -> part 2
    Both parts are "max XOR with a set" queries answered for all nodes at once with a
    bitwise descent using numpy sorts / searchsorted.
    """
    A = [a - 1 for a in A]
    indeg = [0] * N
    for a in A:
        indeg[a] += 1
    order = [i for i in range(N) if indeg[i] == 0]
    h = 0
    while h < len(order):
        u = order[h]
        h += 1
        a = A[u]
        indeg[a] -= 1
        if indeg[a] == 0:
            order.append(a)
    on_cycle = [d > 0 for d in indeg]

    root = list(range(N))
    gid = [0] * N
    preS = [0] * N
    uvals = []
    ugid = []
    cyc_nodes = []
    g = 0
    visited = [False] * N
    for i in range(N):
        if on_cycle[i] and not visited[i]:
            nodes = []
            u = i
            while not visited[u]:
                visited[u] = True
                nodes.append(u)
                u = A[u]
            pre = 0
            pres = []
            for u in nodes:
                gid[u] = g
                preS[u] = pre
                pre ^= V[u]
                pres.append(pre)          
            X = pre
            for p in pres:
                uvals.append(p)
                uvals.append(p ^ X)
            ugid.extend([g] * (2 * len(nodes)))
            cyc_nodes.extend(nodes)
            g += 1

    W = [0] * N
    size = [1] * N
    for u in order:
        size[A[u]] += size[u]
    tin = [0] * N
    nf = [0] * N
    cur = 0
    for c in cyc_nodes:
        tin[c] = cur
        cur += size[c]
        nf[c] = tin[c] + 1
    for u in reversed(order):
        a = A[u]
        W[u] = V[u] ^ W[a]
        root[u] = root[a]
        gid[u] = gid[a]
        t = nf[a]
        tin[u] = t
        nf[a] = t + size[u]
        nf[u] = t + 1

    Wn = np.array(W, dtype=np.int64)
    tin_n = np.array(tin, dtype=np.int64)
    tout_n = tin_n + np.array(size, dtype=np.int64)
    root_n = np.array(root, dtype=np.int64)
    gid_n = np.array(gid, dtype=np.int64)
    preS_n = np.array(preS, dtype=np.int64)

    
    x2 = Wn ^ preS_n[root_n]
    U = np.sort((np.array(ugid, dtype=np.int64) << 30) | np.array(uvals, dtype=np.int64))
    gbase = gid_n << 30
    cur2 = np.zeros(N, dtype=np.int64)
    for b in range(29, -1, -1):
        xb = (x2 >> b) & 1
        pk = (cur2 << 1) | (1 - xb)
        lo = np.searchsorted(U, gbase + (pk << b), 'left')
        hi = np.searchsorted(U, gbase + ((pk + 1) << b), 'left')
        ok = hi > lo
        cur2 = np.where(ok, pk, (cur2 << 1) | xb)
    res = x2 ^ cur2

    
    tree = np.array(order, dtype=np.int64)
    if len(tree):
        x1 = Wn[tree]
        qtin = tin_n[tree]
        sh = 18
        mask = (1 << sh) - 1
        
        by_tin = np.argsort(tin_n, kind='stable')
        el_w = Wn[by_tin]
        el_tin = tin_n[by_tin]
        el_tout = tout_n[by_tin]
        cur1 = np.zeros(len(tree), dtype=np.int64)
        for b in range(29, -1, -1):
            key = el_w >> b
            comp = (key << sh) | el_tin
            idx = np.argsort(comp, kind='stable')
            C = comp[idx]
            RM = np.maximum.accumulate((key[idx] << sh) | el_tout[idx])
            xb = (x1 >> b) & 1
            pk = (cur1 << 1) | (1 - xb)
            pos = np.searchsorted(C, (pk << sh) | qtin, 'left') - 1
            posc = np.maximum(pos, 0)
            r = RM[posc]
            ok = (pos >= 0) & ((r >> sh) == pk) & ((r & mask) > qtin)
            cur1 = np.where(ok, pk, (cur1 << 1) | xb)
        res[tree] = np.maximum(res[tree], x1 ^ cur1)
    return res.tolist()


def main():
    T = int(input())
    for _ in range(T):
        N = int(input())
        A = list(map(int, input().split()))
        V = list(map(int, input().split()))
        print(' '.join(map(str, solve(N, A, V))))

if __name__ == '__main__':
    main()
