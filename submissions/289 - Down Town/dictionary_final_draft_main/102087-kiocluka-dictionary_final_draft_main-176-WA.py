import sys
from bisect import bisect_left


def main():
    data = sys.stdin.buffer.read().split()
    pos = 0
    t = int(data[pos])
    pos += 1
    out = []
    for _ in range(t):
        n = int(data[pos])
        pos += 1
        A = [int(x) - 1 for x in data[pos : pos + n]]
        pos += n
        V = [int(x) for x in data[pos : pos + n]]
        pos += n

        state = [0] * n
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
        recp = [0] * n
        recn = [0] * n
        T = [0] * n

        for cyc in cycles:
            L = len(cyc)
            C = []
            acc = 0
            for v in cyc:
                acc ^= V[v]
                C.append(acc)
            tot = acc
            S = sorted(set(C) | {x ^ tot for x in C})
            hi0 = len(S)

            def best_in_S(x):
                lo, hi = 0, hi0
                cur = 0
                for k in range(29, -1, -1):
                    m = cur | (1 << k)
                    idx = bisect_left(S, m, lo, hi)
                    if (x >> k) & 1:
                        if lo < idx:
                            hi = idx
                        else:
                            lo = idx
                            cur = m
                    else:
                        if idx < hi:
                            lo = idx
                            cur = m
                        else:
                            hi = idx
                return x ^ cur

            for p in range(L):
                c = cyc[p]
                cp = C[p - 1] if p > 0 else 0
                ans[c] = best_in_S(cp)

                if not children[c]:
                    continue

                # dynamic trie (root = node 0)
                ch = [0, 0]  # children of root
                ptr = 1  # next free node id

                # insert 0 (the attachment point) as a full path of bit-0
                node = 0
                for _ in range(30):
                    nxt = ptr
                    ptr += 1
                    ch.extend([0, 0])
                    ch[2 * node] = nxt  # bit 0
                    node = nxt
                T[c] = 0

                stack = list(children[c])
                while stack:
                    u = stack.pop()
                    if u < 0:
                        u = ~u
                        s = recp[u]
                        if s >= 0:
                            ch[s] = 0
                            ptr = recn[u]
                        continue

                    tu = V[u] ^ T[A[u]]
                    T[u] = tu

                    # query maximum XOR with current trie
                    node = 0
                    res = 0
                    for k in range(29, -1, -1):
                        b = (tu >> k) & 1
                        nx = ch[2 * node + (b ^ 1)]
                        if nx:
                            res |= 1 << k
                            node = nx
                        else:
                            node = ch[2 * node + b]
                    r2 = best_in_S(tu ^ cp)
                    ans[u] = res if res > r2 else r2

                    # insert tu
                    node = 0
                    first = -1
                    before = ptr
                    for k in range(29, -1, -1):
                        b = (tu >> k) & 1
                        idx = 2 * node + b
                        nx = ch[idx]
                        if nx == 0:
                            nx = ptr
                            ptr += 1
                            ch.extend([0, 0])
                            ch[idx] = nx
                            if first < 0:
                                first = idx
                        node = nx
                    recp[u] = first
                    recn[u] = before
                    stack.append(~u)
                    stack.extend(children[u])

                # clean root for the next attachment point (optional but safe)
                ch[0] = ch[1] = 0

        out.append(" ".join(map(str, ans)))
    sys.stdout.write("\n".join(out))


if __name__ == "__main__":
    main()
