from array import array

_MASKS = [1 << b for b in range(29, 0, -1)]


def solve(N: int, A: list[int], V: list[int]) -> list[int]:
    """
    Return an array of N integers, the i-th of which
    represents Big Ben's maximum happiness if he
    starts by trying to define word i.

    N: the number of words in the dictionary
    A: the first word in the definition of word i
    V: the value associated with the happiness of each word
    """
    nxt = [a - 1 for a in A]
    indeg = [0] * N
    for a in nxt:
        indeg[a] += 1
    stack = [i for i in range(N) if indeg[i] == 0]
    order = []
    while stack:
        u = stack.pop()
        order.append(u)
        p = nxt[u]
        indeg[p] -= 1
        if indeg[p] == 0:
            stack.append(p)
    ntree = len(order)
    ncyc = N - ntree

    size = 31 * (ntree + 2 * ncyc + 2) + 4
    L = array('i', [0]) * size
    R = array('i', [0]) * size
    cnt = 2

    ans = [0] * N
    wroot = [0] * N
    D = [0] * N
    masks = _MASKS

    seen = [False] * N
    for s in range(N):
        if indeg[s] == 0 or seen[s]:
            continue
        cyc = []
        u = s
        while not seen[u]:
            seen[u] = True
            cyc.append(u)
            u = nxt[u]
        q = 0
        Qs = []
        for u in cyc:
            Qs.append(q)
            q ^= V[u]
        c = q
        root = cnt
        cnt += 1
        for val in Qs + [x ^ c for x in Qs]:
            cur = root
            for m in masks:
                if val & m:
                    n2 = R[cur]
                    if not n2:
                        n2 = cnt
                        cnt += 1
                        R[cur] = n2
                else:
                    n2 = L[cur]
                    if not n2:
                        n2 = cnt
                        cnt += 1
                        L[cur] = n2
                cur = n2
            if val & 1:
                R[cur] = 1
            else:
                L[cur] = 1
        for k, u in enumerate(cyc):
            key = Qs[k]
            node = root
            res = 0
            for m in masks:
                if key & m:
                    w = L[node]
                    if w:
                        node = w
                        res |= m
                    else:
                        node = R[node]
                else:
                    w = R[node]
                    if w:
                        node = w
                        res |= m
                    else:
                        node = L[node]
            if key & 1:
                if L[node]:
                    res |= 1
            else:
                if R[node]:
                    res |= 1
            ans[u] = res
            D[u] = key
            wroot[u] = root

    for i in reversed(order):
        p = nxt[i]
        d = V[i] ^ D[p]
        D[i] = d
        n = old = wroot[p]
        cn = new = cnt
        cnt += 1
        r = 0
        for m in masks:
            nn = cnt
            cnt += 1
            if d & m:
                w = L[n]
                if w:
                    n = w
                    r |= m
                else:
                    n = R[n]
                L[cn] = L[old]
                R[cn] = nn
                old = R[old]
            else:
                w = R[n]
                if w:
                    n = w
                    r |= m
                else:
                    n = L[n]
                R[cn] = R[old]
                L[cn] = nn
                old = L[old]
            cn = nn
        if d & 1:
            if L[n]:
                r |= 1
            L[cn] = L[old]
            R[cn] = 1
        else:
            if R[n]:
                r |= 1
            R[cn] = R[old]
            L[cn] = 1
        ans[i] = r
        wroot[i] = new
    return ans


def main():
    T = int(input())
    for _ in range(T):
        N = int(input())
        A = list(map(int, input().split()))
        V = list(map(int, input().split()))
        print(' '.join(map(str, solve(N, A, V))))

if __name__ == '__main__':
    main()
