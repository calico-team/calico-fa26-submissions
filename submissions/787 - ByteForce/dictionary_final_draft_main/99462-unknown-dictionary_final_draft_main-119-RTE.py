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
    cnt = {}
    get = cnt.get
    shifts = [(b, 1 << (30 - b)) for b in range(30)]
    qshifts = [(b, 1 << (30 - b)) for b in range(29, -1, -1)]

    for c in range(N):
        if indeg[c] > 0 and children[c]:
            cnt.clear()
            for b, off in shifts:
                cnt[off] = 1           
            stack = [(c, 0, True)]
            while stack:
                u, state, keep = stack.pop()
                if state:
                    for b, off in shifts:
                        k = (W[u] >> b) + off
                        t = cnt[k] - 1
                        if t:
                            cnt[k] = t
                        else:
                            del cnt[k]
                    continue
                ch = children[u]
                if u != c:
                    x = W[u]
                    cur = 0
                    for b, off in qshifts:
                        if (x >> b) & 1:
                            pk = cur << 1
                        else:
                            pk = (cur << 1) | 1
                        if (pk + off) in cnt:
                            cur = pk
                        else:
                            cur = pk ^ 1
                    v = x ^ cur
                    if v > res[u]:
                        res[u] = v
                    if ch:
                        for b, off in shifts:
                            k = (x >> b) + off
                            cnt[k] = get(k, 0) + 1
                        if not keep:
                            stack.append((u, 1, False))
                if ch:
                    if len(ch) > 1:
                        hv = max(ch, key=size.__getitem__)
                        stack.append((hv, 0, keep))   
                        for v2 in ch:
                            if v2 != hv:
                                stack.append((v2, 0, False))
                    else:
                        stack.append((ch[0], 0, keep))
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
