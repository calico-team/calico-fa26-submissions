import sys

def go(N, A, V):
    ans = [0] * (N + 1)
    st = [0] * (N + 1)
    oncyc = [False] * (N + 1)
    cycles = []

    # find the cycles first
    for i in range(1, N + 1):
        if st[i]:
            continue
        path = []
        u = i
        while st[u] == 0:
            st[u] = 1
            path.append(u)
            u = A[u]
        if st[u] == 1:
            idx = path.index(u)
            cyc = path[idx:]
            for v in cyc:
                oncyc[v] = True
            cycles.append(cyc)
        for v in path:
            st[v] = 2

    # everything not on a cycle is a tree hanging off it
    ch = [[] for _ in range(N + 1)]
    for u in range(1, N + 1):
        if not oncyc[u]:
            ch[A[u]].append(u)

    for cyc in cycles:
        L = len(cyc)
        D = [0] * (L + 1)
        for k in range(L):
            D[k + 1] = D[k] ^ V[cyc[k]]
        c = D[L]

        # count-based trie, key = (bit level, y >> level)
        cnt = {}

        def ins(y, delta):
            for b in range(30):
                key = (b << 30) | (y >> b)
                cnt[key] = cnt.get(key, 0) + delta

        def query(x):
            # best (y ^ x) among stored y
            res = 0
            cur = 0
            for b in range(29, -1, -1):
                xb = (x >> b) & 1
                want = xb ^ 1
                cand = (cur << 1) | want
                if cnt.get((b << 30) | cand, 0) > 0:
                    cur = cand
                    res |= 1 << b
                else:
                    cur = (cur << 1) | xb
            return res

        seed = [D[r] for r in range(L)] + [D[r] ^ c for r in range(L)]
        for a in seed:
            ins(a, 1)

        for s in range(L):
            node = cyc[s]
            mask = D[s]
            ans[node] = query(mask)
            stack = [(x, False) for x in ch[node]]
            while stack:
                v, done = stack.pop()
                if not done:
                    mask ^= V[v]
                    ins(mask, 1)
                    ans[v] = query(mask)
                    stack.append((v, True))
                    for x in ch[v]:
                        stack.append((x, False))
                else:
                    ins(mask, -1)
                    mask ^= V[v]

    return ans[1:]

def main():
    d = sys.stdin.read().split()
    p = 0
    T = int(d[p]); p += 1
    out = []
    for _ in range(T):
        N = int(d[p]); p += 1
        A = [0] + [int(x) for x in d[p:p+N]]; p += N
        V = [0] + [int(x) for x in d[p:p+N]]; p += N
        out.append(" ".join(map(str, go(N, A, V))))
    sys.stdout.write("\n".join(out))

if __name__ == "__main__":
    main()