import sys
from bisect import bisect_left


def main():
    data = sys.stdin.buffer.read().split()
    pos = 0
    t = int(data[pos])
    pos += 1
    out = []
    M = (1 << 30) - 1
    for _ in range(t):
        n = int(data[pos])
        pos += 1
        A = [int(x) - 1 for x in data[pos : pos + n]]
        pos += n
        V = [int(x) for x in data[pos : pos + n]]
        pos += n

        # find cycle nodes
        state = [0] * n  # 0 unvisited, 1 in progress, 2 done
        on_cycle = [False] * n
        cycles = []
        for s0 in range(n):
            if state[s0]:
                continue
            path = []
            u = s0
            while state[u] == 0:
                state[u] = 1
                path.append(u)
                u = A[u]
            if state[u] == 1:
                cyc = path[path.index(u) :]
                for v in cyc:
                    on_cycle[v] = True
                cycles.append(cyc)
            for v in path:
                state[v] = 2
        children = [[] for _ in range(n)]
        for i in range(n):
            if not on_cycle[i]:
                children[A[i]].append(i)

        ans = [0] * n

        def query_sorted(s, x):
            lo, hi = 0, len(s)
            cur = 0
            for k in range(29, -1, -1):
                m = cur | (1 << k)
                idx = bisect_left(s, m, lo, hi)
                if (x >> k) & 1:  # want bit 0
                    if lo < idx:
                        hi = idx
                    else:
                        lo = idx
                        cur = m
                else:  # want bit 1
                    if idx < hi:
                        lo = idx
                        cur = m
                    else:
                        hi = idx
            return x ^ cur

        for cyc in cycles:
            L = len(cyc)
            C = []
            acc = 0
            for v in cyc:
                acc ^= V[v]
                C.append(acc)
            tot = acc
            s = sorted(set(C) | set(c ^ tot for c in C))
            cprev = [0] + C[:-1]
            for p in range(L):
                c = cyc[p]
                base = cprev[p]
                ans[c] = query_sorted(s, base)

            # dynamic trie (dict of counts) for tree paths
            for p in range(L):
                c = cyc[p]
                cp = cprev[p]
                cnt = {}

                def add(x, d):
                    cur = 1
                    for k in range(29, -1, -1):
                        cur = cur * 2 + ((x >> k) & 1)
                        cnt[cur] = cnt.get(cur, 0) + d

                def qry(x):
                    cur = 1
                    for k in range(29, -1, -1):
                        bit = (x >> k) & 1
                        w = cur * 2 + (bit ^ 1)
                        if cnt.get(w, 0) > 0:
                            cur = w
                        else:
                            cur = cur * 2 + bit
                    return x ^ (cur & M)

                if not children[c]:
                    continue
                T = {c: 0}
                add(0, 1)
                stack = []
                for ch in children[c]:
                    stack.append((ch, 0))
                while stack:
                    u, flag = stack.pop()
                    if flag:
                        add(T[u], -1)
                        continue
                    tu = V[u] ^ T[A[u]]
                    T[u] = tu
                    r1 = qry(tu)
                    r2 = query_sorted(s, tu ^ cp)
                    ans[u] = r1 if r1 > r2 else r2
                    add(tu, 1)
                    stack.append((u, 1))
                    for ch in children[u]:
                        stack.append((ch, 0))
        out.append(" ".join(map(str, ans)))
    print("\n".join(out))


main()
