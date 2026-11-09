from bisect import bisect_left


def solve(N, A, V):
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


    visited = [False] * N
    cyc_of = [-1] * N          
    preS = [0] * N
    sets = []
    cycles = []
    for i in range(N):
        if indeg[i] > 0 and not visited[i]:
            nodes = []
            u = i
            while not visited[u]:
                visited[u] = True
                nodes.append(u)
                u = A[u]
            g = len(sets)
            pre = 0
            pres = []
            for u in nodes:
                cyc_of[u] = g
                preS[u] = pre
                pre ^= V[u]
                pres.append(pre)
            X = pre
            s = set(pres)
            s.update([p ^ X for p in pres])
            sets.append(sorted(s))
            cycles.append(nodes)

    def best_in(U, x):
        lo, hi = 0, len(U)
        pre = 0
        b = 29
        while hi - lo > 1:
            m = bisect_left(U, (pre << (b + 1)) | (1 << b), lo, hi)
            if (x >> b) & 1:
                if lo < m:
                    hi = m
                    pre <<= 1
                else:
                    lo = m
                    pre = (pre << 1) | 1
            else:
                if m < hi:
                    lo = m
                    pre = (pre << 1) | 1
                else:
                    hi = m
                    pre <<= 1
            b -= 1
        return x ^ U[lo]

    res = [0] * N
    W = [0] * N
    root = list(range(N))
    for u in reversed(order):
        a = A[u]
        W[u] = V[u] ^ W[a]
        root[u] = root[a]
    for u in range(N):
        r = root[u]
        res[u] = best_in(sets[cyc_of[r]], W[u] ^ preS[r])

   
    children = [[] for _ in range(N)]
    for u in order:
        children[A[u]].append(u)
    size = [1] * N
    for u in order:
        size[A[u]] += size[u]
    from array import array
    cap = 30 * (sum(1 for u in range(N) if children[u]) + 1) + 2
    ch2 = array('i', bytes(4 * 2 * cap))   # children: node*2 + bit
    cnt = array('i', bytes(4 * cap))
    used = [1]                             # node 0 = trie root
    bits = list(range(29, -1, -1))

    def insert(w, d):
        node = 0
        for b in bits:
            i = node * 2 + ((w >> b) & 1)
            nd = ch2[i]
            if not nd:
                nd = used[0]
                used[0] = nd + 1
                ch2[i] = nd
            cnt[nd] += d
            node = nd

    def remove(w):
        node = 0
        for b in bits:
            node = ch2[node * 2 + ((w >> b) & 1)]
            cnt[node] -= 1

    for c in range(N):
        if indeg[c] > 0 and children[c]:
            # reset trie
            for i in range(used[0] * 2):
                ch2[i] = 0
            for i in range(used[0]):
                cnt[i] = 0
            used[0] = 1
            insert(0, 1)                    # W(root) = 0
            stack = [(c, 0, True)]
            while stack:
                u, state, keep = stack.pop()
                if state:
                    remove(W[u])
                    continue
                chl = children[u]
                if u != c:
                    x = W[u]
                    node = 0
                    v = 0
                    for b in bits:
                        bit = (x >> b) & 1
                        nd = ch2[node * 2 + (bit ^ 1)]
                        if nd and cnt[nd]:
                            node = nd
                            v |= 1 << b
                        else:
                            node = ch2[node * 2 + bit]
                    if v > res[u]:
                        res[u] = v
                    if chl:
                        insert(x, 1)
                        if not keep:
                            stack.append((u, 1, False))
                if chl:
                    if len(chl) > 1:
                        hv = max(chl, key=size.__getitem__)
                        stack.append((hv, 0, keep))   
                        for v2 in chl:
                            if v2 != hv:
                                stack.append((v2, 0, False))
                    else:
                        stack.append((chl[0], 0, keep))
    return res


def main():
    T = int(input())
    for _ in range(T):
        N = int(input())
        A = list(map(int, input().split()))
        V = list(map(int, input().split()))
        print(' '.join(map(str, solve(N, A, V))))

if __name__ == '__main__':
    main()
